#ifndef OGL_RENDERMESH_INCLUDED
#define OGL_RENDERMESH_INCLUDED

#include "GLSim/core/Mesh.h"
#include "GL/glew.h"
#include "Component.h"


namespace ogl { class RenderMesh; }
class RenderMesh : public Mesh, public Component
{
public:
	RenderMesh();
	~RenderMesh();

	//void initGL();
	void receiveMessage(Message&);
	void setVertices(const std::vector<GLfloat>&, const std::vector<GLushort>&, const std::vector<GLfloat>&);
	void render();

private:
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_vao;
};

#endif