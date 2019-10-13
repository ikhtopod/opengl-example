#include "stdafx.h"
#include "Mesh.h"

const GLsizei Mesh::DEFAULT_BUFFER_SIZE = 1;

void Mesh::Unbind() {
	glBindVertexArray(0);
}

void Mesh::SetVertices(const std::vector<VerticesType>& vertices) {
	JustUtility::CopyVector<VerticesType>(vertices, m_vertices);
}

void Mesh::SetIndices(const std::vector<GLuint>& indices) {
	JustUtility::CopyVector<GLuint>(indices, m_indices);
}

Shader& Mesh::GetShader() {
	return m_shader;
}

/* IRendering */

void Mesh::Init() {
	glGenVertexArrays(Mesh::DEFAULT_BUFFER_SIZE, &vao);
	glGenBuffers(Mesh::DEFAULT_BUFFER_SIZE, &vbo);
	glGenBuffers(Mesh::DEFAULT_BUFFER_SIZE, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		static_cast<GLsizeiptr>(m_vertices.size()) * sizeof(VerticesType),
		&m_vertices[0],
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		static_cast<GLsizeiptr>(m_indices.size()) * sizeof(GLuint),
		&m_indices[0],
		GL_STATIC_DRAW);

	/* layouts */
	glEnableVertexAttribArray(JustUtility::AttribIndex::POSITION);
	glVertexAttribPointer(JustUtility::AttribIndex::POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));

	/* vertex normals example
	glEnableVertexAttribArray(MeshBase::AttribIndex::NORMAL);
	glVertexAttribPointer(MeshBase::AttribIndex::NORMAL, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, normal)); */

	m_shader.Init();

	Mesh::Unbind();
}

void Mesh::Draw() {
	m_shader.Draw();

	glBindVertexArray(vao);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(m_mode, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
	Mesh::Unbind();
}

void Mesh::Free() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	m_shader.Free();
}
