#include "OBJModel.h"

OBJModel::OBJModel(
	const std::string& objfile,
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Model(dxdevice, dxdevice_context)
{
	// Load the OBJ
	OBJLoader* mesh = new OBJLoader();
	mesh->Load(objfile);

	// Load and organize indices in ranges per drawcall (material)

	std::vector<unsigned> indices;
	unsigned int indexOffset = 0;

	for (auto& dc : mesh->Drawcalls)
	{
		// Append the drawcall indices
		for (auto& tri : dc.Triangles)
			indices.insert(indices.end(), tri.VertexIndices, tri.VertexIndices + 3);

		// Create a range
		unsigned int indexSize = (unsigned int)dc.Triangles.size() * 3;
		int materialIndex = dc.MaterialIndex > -1 ? dc.MaterialIndex : -1;
		m_index_ranges.push_back({ indexOffset, indexSize, 0, materialIndex });

		indexOffset = (unsigned int)indices.size();
	}
	for (int i = 0; i < indices.size(); i += 3) // For all triangles
		compute_TB(
			mesh->Vertices[indices[i + 0]],
			mesh->Vertices[indices[i + 1]],
			mesh->Vertices[indices[i + 2]]);

	// Vertex array descriptor
	D3D11_BUFFER_DESC vertexbufferDesc = { 0 };
	vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexbufferDesc.CPUAccessFlags = 0;
	vertexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexbufferDesc.MiscFlags = 0;
	vertexbufferDesc.ByteWidth = (UINT)(mesh->Vertices.size() * sizeof(Vertex));
	// Data resource
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = &(mesh->Vertices)[0];
	// Create vertex buffer on device using descriptor & data
	dxdevice->CreateBuffer(&vertexbufferDesc, &vertexData, &m_vertex_buffer);
	SETNAME(m_vertex_buffer, "VertexBuffer");

	// Index array descriptor
	D3D11_BUFFER_DESC indexbufferDesc = { 0 };
	indexbufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexbufferDesc.CPUAccessFlags = 0;
	indexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexbufferDesc.MiscFlags = 0;
	indexbufferDesc.ByteWidth = (UINT)(indices.size() * sizeof(unsigned));
	// Data resource
	D3D11_SUBRESOURCE_DATA indexData = { 0 };
	indexData.pSysMem = &indices[0];
	// Create index buffer on device using descriptor & data
	dxdevice->CreateBuffer(&indexbufferDesc, &indexData, &m_index_buffer);
	SETNAME(m_index_buffer, "IndexBuffer");

	// Copy materials from mesh
	append_materials(mesh->Materials);

	// Go through materials and load textures (if any) to device
	std::cout << "Loading textures..." << std::endl;
	for (auto& material : m_materials)
	{
		HRESULT hr;

		// Load Diffuse texture
		//
		if (material.DiffuseTextureFilename.size()) {

			hr = LoadTextureFromFile(
				dxdevice,
				material.DiffuseTextureFilename.c_str(),
				&material.DiffuseTexture);
			std::cout << "\t" << material.DiffuseTextureFilename
				<< (SUCCEEDED(hr) ? " - OK" : "- FAILED") << std::endl;
		}

		// + other texture types here - see Material class
		// ...
	}
	std::cout << "Done." << std::endl;
	for (auto& material : m_materials)
	{
		HRESULT hr;

		// Load Diffuse texture
		//
		if (material.NormalTextureFilename.size()) {

			hr = LoadTextureFromFile(
				dxdevice,
				material.NormalTextureFilename.c_str(),
				&material.NormalTexture);
		
		}

		// + other texture types here - see Material class
		// ...
	}
	std::cout << "Done." << std::endl;

	SAFE_DELETE(mesh);
}

void OBJModel::Render(ID3D11Buffer* material_buffer) const
{
	// Bind vertex buffer
	const UINT32 stride = sizeof(Vertex);
	const UINT32 offset = 0;
	m_dxdevice_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);

	// Bind index buffer
	m_dxdevice_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// Iterate Drawcalls
	for (auto& indexRange : m_index_ranges)
	{
		// Fetch material
		const Material& material = m_materials[indexRange.MaterialIndex];

		UpdateMaterialBuffer(material_buffer,
			(material.AmbientColour.x, material.AmbientColour.y, material.AmbientColour.z,1.0f),
			(material.DiffuseColour.x, material.DiffuseColour.y, material.DiffuseColour.z, 1.0f),
			(material.SpecularColour.x, material.SpecularColour.y, material.SpecularColour.z, 1.0f));

		// Bind diffuse texture to slot t0 of the PS
		m_dxdevice_context->PSSetShaderResources(0, 1, &material.DiffuseTexture.TextureView);
		m_dxdevice_context->PSSetShaderResources(1, 1, &material.NormalTexture.TextureView);
		// + bind other textures here, e.g. a normal map, to appropriate slots

		// Make the drawcall
		m_dxdevice_context->DrawIndexed(indexRange.Size, indexRange.Start, 0);
	}
}
void OBJModel::UpdateMaterialBuffer(ID3D11Buffer* material_buffer, 
	vec4f Ambient, vec4f Diffuse, vec4f Specular) const
{
	// Map the resource buffer, obtain a pointer and then write our matrices to it
	D3D11_MAPPED_SUBRESOURCE resource;
	m_dxdevice_context->Map(material_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	MaterialBuffer* matrixBuffer = (MaterialBuffer*)resource.pData;
	matrixBuffer->Ambient = Ambient;
	matrixBuffer->Diffuse = Diffuse;
	matrixBuffer->Specular = Specular;
	m_dxdevice_context->Unmap(material_buffer, 0);
}
void OBJModel::compute_TB(Vertex& v0, Vertex& v1, Vertex& v2)
{
	vec3f tangent, binormal;
	vec3f D, E;
	vec2f F, G;
	D = v1.Position - v0.Position;
	E = v2.Position - v0.Position;
	F = v1.TexCoord - v0.TexCoord;
	G = v2.TexCoord - v0.TexCoord;
	float det = 1 / (F.x * G.y - F.y * G.x);

	tangent = (D * G.y + E * -F.y) * det;
	binormal = (D * -G.x + E * F.x) * det;

	v0.Tangent = v1.Tangent = v2.Tangent = normalize(tangent);
	v0.Binormal = v1.Binormal = v2.Binormal = normalize(binormal);
}

OBJModel::~OBJModel()
{
	for (auto& material : m_materials)
	{
		SAFE_RELEASE(material.DiffuseTexture.TextureView);

		// Release other used textures ...
	}
}