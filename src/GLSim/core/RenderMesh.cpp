#include "GLSim/core/RenderMesh.h"
#include "GLSim/core/TextureManager.h"

RenderMesh::RenderMesh()
	: Mesh(),
	Component(COMPONENT_TYPE::RENDER_MESH),
	m_vao(0),
	m_vbo(0),
	m_ibo(0)
{
	p_material = new Material;
	assert(p_material != nullptr);
	p_material->setTexIndex(TextureManager::LoadTexture("C:/Projects/3Dsim/res/textures/gradient.png", TEXTURE_2D));
	assert(p_material->getTexIndex() != -1);

	////VAO////
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	////VBO////
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	//position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//Normal data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	//UV data
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)*2));

	///IBO///
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
		render(static_cast<MessageRender&>(message).getShaderManager());
		break;
	default:
		break;
	}
}

void RenderMesh::setVertices(const std::vector<Vertex>& verts, const std::vector<GLushort>& indices)
{
	Mesh::setVertices(verts, indices);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLushort), &m_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderMesh::render(ShaderManager* shdrManager)
{
	glBindVertexArray(m_vao);
	
	if(p_material->getTexIndex() != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureManager::getTexture(p_material->getTexIndex()));
		shdrManager->setUniform("tex", 0);
	}


	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, m_vertices.size()/2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}