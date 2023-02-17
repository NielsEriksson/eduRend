
#include "model.h"
class Cube : public Model
{
	unsigned m_number_of_indices = 0;

public:

	Cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context);


	virtual void Render(ID3D11Buffer* material_buffer) const;

	std::vector<Material> m_materials;

	void append_materials(const std::vector<Material>& mtl_vec)
	{
		m_materials.insert(m_materials.end(), mtl_vec.begin(), mtl_vec.end());
	}
	~Cube() { }
};
