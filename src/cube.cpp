
#include "cube.h"

Cube::Cube(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Model(dxdevice, dxdevice_context)
{
	// Vertex and index arrays
	// Once their data is loaded to GPU buffers, they are not needed anymore
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	// Populate the vertex array with 4 Vertices
	Vertex v0, v1, v2, v3, v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23;
	//FRONT
	v0.Position = { -0.5, -0.5f, 0.5f };
	v0.Normal = { 0, 0, 1 };
	v0.TexCoord = { 0, 0 };
	v1.Position = { 0.5, -0.5f, 0.5f };
	v1.Normal = { 0, 0, 1 };
	v1.TexCoord = { 0, 1 };
	v2.Position = { 0.5, 0.5f, 0.5f };
	v2.Normal = { 0, 0, 1 };
	v2.TexCoord = { 1, 1 };
	v3.Position = { -0.5, 0.5f, 0.5f };
	v3.Normal = { 0, 0, 1 };
	v3.TexCoord = { 1, 0 };

	//BACK
	v4.Position = { -0.5, -0.5f, -0.5f };
	v4.Normal = { 0, 0, 1 };
	v4.TexCoord = { 0, 0 };
	v5.Position = { 0.5, -0.5f, -0.5f };
	v5.Normal = { 0, 0, 1 };
	v5.TexCoord = { 0, 1 };
	v6.Position = { 0.5, 0.5f, -0.5f };
	v6.Normal = { 0, 0, 1 };
	v6.TexCoord = { 1, 1 };
	v7.Position = { -0.5, 0.5f, -0.5f };
	v7.Normal = { 0, 0, 1 };
	v7.TexCoord = { 1, 0 };

	//LEFT
	v8.Position = { -0.5, -0.5f, -0.5f };;
	v8.Normal = { 0, 0, 1 };
	v8.TexCoord = { 0, 0 };
	v9.Position = { -0.5, -0.5f, 0.5f };
	v9.Normal = { 0, 0, 1 };
	v9.TexCoord = { 0, 1 };
	v10.Position = {-0.5, 0.5f, 0.5f };
	v10.Normal = { 0, 0, 1 };
	v10.TexCoord = { 1, 1 };
	v11.Position = { -0.5, 0.5f, -0.5f };
	v11.Normal = { 0, 0, 1 };
	v11.TexCoord = { 1, 0 };
	//RIGHT
	v12.Position = { 0.5, -0.5f, -0.5f };;
	v12.Normal = { 0, 0, 1 };
	v12.TexCoord = { 0, 0 };
	v13.Position = { 0.5, -0.5f, 0.5f };
	v13.Normal = { 0, 0, 1 };
	v13.TexCoord = { 0, 1 };
	v14.Position = { 0.5, 0.5f, 0.5f };
	v14.Normal = { 0, 0, 1 };
	v14.TexCoord = { 1, 1 };
	v15.Position = { 0.5, 0.5f, -0.5f };
	v15.Normal = { 0, 0, 1 };
	v15.TexCoord = { 1, 0 };
	//TOP
	v20.Position = { -0.5, -0.5f, -0.5f };
	v20.Normal = { 0, 0, 1 };
	v20.TexCoord = { 0, 0 };
	v21.Position = { 0.5, -0.5f, -0.5f };
	v21.Normal = { 0, 0, 1 };
	v21.TexCoord = { 0, 1 };
	v22.Position = { 0.5, 0.5f, -0.5f };
	v22.Normal = { 0, 0, 1 };
	v22.TexCoord = { 1, 1 };
	v23.Position = { -0.5, 0.5f, -0.5f };
	v23.Normal = { 0, 0, 1 };
	v23.TexCoord = { 1, 0 };
	//BOTTOM
	v8.Position = { -0.5, -0.5f, -0.5f };
	v8.Normal = { 0, 0, 1 };
	v8.TexCoord = { 0, 0 };
	v9.Position = { 0.5, -0.5f, -0.5f };
	v9.Normal = { 0, 0, 1 };
	v9.TexCoord = { 0, 1 };
	v10.Position = { 0.5, 0.5f, -0.5f };
	v10.Normal = { 0, 0, 1 };
	v10.TexCoord = { 1, 1 };
	v11.Position = { -0.5, 0.5f, -0.5f };
	v11.Normal = { 0, 0, 1 };
	v11.TexCoord = { 1, 0 };
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);

	// Populate the index array with two triangles
	// Triangle #1
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	// Triangle #2
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	// Triangle #3
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(6);
	// Triangle #4
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(6);
	// Triangle #5
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(6);
	// Triangle #6
	indices.push_back(2);
	indices.push_back(7);
	indices.push_back(6);
	// Triangle #7
	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(2);
	// Triangle #8
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(2);
	// Triangle #9
	indices.push_back(3);
	indices.push_back(7);
	indices.push_back(4);
	// Triangle #10
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(0);
	// Triangle #11
	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(1);
	// Triangle #12
	indices.push_back(1);
	indices.push_back(4);
	indices.push_back(5);
	
	// Vertex array descriptor
	D3D11_BUFFER_DESC vertexbufferDesc{ 0 };
	vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexbufferDesc.CPUAccessFlags = 0;
	vertexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexbufferDesc.MiscFlags = 0;
	vertexbufferDesc.ByteWidth = (UINT)(vertices.size() * sizeof(Vertex));
	// Data resource
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = &vertices[0];
	// Create vertex buffer on device using descriptor & data
	dxdevice->CreateBuffer(&vertexbufferDesc, &vertexData, &m_vertex_buffer);
	SETNAME(m_vertex_buffer, "VertexBuffer");

	//  Index array descriptor
	D3D11_BUFFER_DESC indexbufferDesc = { 0 };
	indexbufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexbufferDesc.CPUAccessFlags = 0;
	indexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexbufferDesc.MiscFlags = 0;
	indexbufferDesc.ByteWidth = (UINT)(indices.size() * sizeof(unsigned));
	// Data resource
	D3D11_SUBRESOURCE_DATA indexData{ 0 };
	indexData.pSysMem = &indices[0];
	// Create index buffer on device using descriptor & data
	dxdevice->CreateBuffer(&indexbufferDesc, &indexData, &m_index_buffer);
	SETNAME(m_index_buffer, "IndexBuffer");

	m_number_of_indices = (unsigned int)indices.size();
}


void Cube::Render() const
{
	// Bind our vertex buffer
	const UINT32 stride = sizeof(Vertex); //  sizeof(float) * 8;
	const UINT32 offset = 0;
	m_dxdevice_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);

	// Bind our index buffer
	m_dxdevice_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// Make the drawcall
	m_dxdevice_context->DrawIndexed(m_number_of_indices, 0, 0);
}