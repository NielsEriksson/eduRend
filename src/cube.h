
#include "model.h"
class Cube : public Model
{
	unsigned m_number_of_indices = 0;

public:

	Cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context);


	virtual void Render(ID3D11Buffer* material_buffer) const;


	~Cube() { }
};
