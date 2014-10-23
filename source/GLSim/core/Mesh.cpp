#include "GLSim/core/Mesh.h"

Mesh::Mesh()
	: m_vertices()
{

}

Mesh::~Mesh()
{
	std::vector<GLfloat>().swap(m_vertices);
}

void Mesh::setVertices(const std::vector<GLfloat>& verts, const std::vector<GLushort>& indices, const std::vector<GLfloat>& normals)
{
	m_vertices = verts;
	m_indices = indices;
	m_normals = normals;
}