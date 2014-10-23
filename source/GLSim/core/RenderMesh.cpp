#include "GLSim/core/RenderMesh.h"

RenderMesh::RenderMesh()
	: Mesh(),
	Component(COMPONENT_TYPE::RENDER_MESH),
	m_vao(0),
	m_vbo(0),
	m_ibo(0)
{
	////VAO////
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	////VBO////
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	//Normal data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(sizeof(float) * 3));

	///IBO///
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBindVertexArray(0);
}

RenderMesh::~RenderMesh()
{
	
}

//void RenderMesh::initGL(){ }

void RenderMesh::receiveMessage(Message& message)
{
	switch(message.getType())
	{
	case Message::MESSAGE_TYPES::RENDER:
		render();
		break;
	default:
		break;
	}
}

void RenderMesh::setVertices(const std::vector<GLfloat>& verts, const std::vector<GLushort>& indices, const std::vector<GLfloat>& normals)
{
	Mesh::setVertices(verts, indices, normals);
	std::vector<GLfloat> data;
	for(unsigned int i = 0; i < m_vertices.size(); i += 3)
	{
		data.push_back(m_vertices[i]);
		data.push_back(m_vertices[i + 1]);
		data.push_back(m_vertices[i + 2]);

		data.push_back(m_normals[i]);
		data.push_back(m_normals[i + 1]);
		data.push_back(m_normals[i + 2]);
	}

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLushort), &m_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void RenderMesh::render()
{
	glBindVertexArray(m_vao);
	///Set uniforms
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glBindVertexArray(0);
}