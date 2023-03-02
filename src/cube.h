
#include "model.h"
#include "Buffers.h"


class Cube : public Model
{
	unsigned m_number_of_indices = 0;

public:

	Cube(ID3D11Device* dxdevice, const char* texturefile,
		ID3D11DeviceContext* dxdevice_context);
	
	Material material;

	virtual void Render(ID3D11Buffer* material_buffer) const;
	~Cube() { }
	void UpdateMaterialBuffer(ID3D11Buffer* material_buffer,
		vec4f Ambient, vec4f Diffuse, vec4f Specular) const;
};
