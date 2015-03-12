#ifndef OGL_MESH_INCLUDED
#define OGL_MESH_INCLUDED

#include "GL/glew.h"
#include <vector>
#include "glm/glm.hpp"

namespace ogl { struct Vertex; }
struct Vertex
{
	Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 u)
	{
		position = p;
		normal = n;
		uv = u;
	}

	Vertex()
	{
		position = glm::vec3(0,0,0);
		normal = glm::vec3(0,0,0);
		uv = glm::vec2(0, 0);
	}

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

//todo: MeshId for shared mesh comps
namespace ogl { class Mesh; }
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void setVertices(const std::vector<Vertex>& verts, const std::vector<GLushort>& indices);

protected:

	std::vector<Vertex> m_vertices;
	std::vector<GLushort> m_indices;
};

#endif