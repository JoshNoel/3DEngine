#include "GLSim/core/Mesh.h"

Mesh::Mesh()
	: m_vertices()
{

}

Mesh::~Mesh()
{
	std::vector<Vertex>().swap(m_vertices);
}

void Mesh::setVertices(const std::vector<Vertex>& verts, const std::vector<GLushort>& indices)
{
	m_vertices = verts;
	m_indices = indices;
}