#ifndef OGL_RENDERMESH_INCLUDED
#define OGL_RENDERMESH_INCLUDED

#include "GLSim/core/Mesh.h"
#include "GL/glew.h"
#include "Component.h"
#include "GLSim/core/Material.h"


namespace ogl { class RenderMesh; }
class RenderMesh : public Mesh, public Component
{
public:
	RenderMesh();
	~RenderMesh();

	//void initGL();
	void receiveMessage(Message&);
	void setVertices(const std::vector<Vertex>&, const std::vector<GLushort>&);
	void render(ShaderManager* manager);
	///void setMaterial(Material* material) { p_material = material; }
	Material* getMaterial() { return p_material; }

private:
	Material* p_material;
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_vao;
};

#endif