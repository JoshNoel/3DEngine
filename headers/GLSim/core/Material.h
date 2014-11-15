#ifndef OGL_MATERIAL_INCLUDED
#define OGL_MATERIAL_INCLUDED

namespace ogl { class Material; }
class Material
{
public:
	Material();
	~Material();

	int getTexIndex() { return texIndex; }
	void setTexIndex(int val) { texIndex = val; }

private:
	int texIndex;

};
#endif