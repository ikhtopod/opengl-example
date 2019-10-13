#pragma once

#ifndef MESH_H
#define MESH_H

#include "IRendering.h"
#include "Shader.h"

class Mesh : virtual public IRendering {
	using VerticesType = glm::vec3;

protected:
	static const GLsizei DEFAULT_BUFFER_SIZE;

protected:
	GLenum m_mode = GL_TRIANGLES;

	std::vector<VerticesType> m_vertices {};
	std::vector<GLuint> m_indices {};

	GLuint vao {};
	GLuint vbo {};
	GLuint ebo {};

	Shader m_shader {};

protected:
	static void Unbind();

public:
	void SetVertices(const std::vector<VerticesType>& vertices);
	void SetIndices(const std::vector<GLuint>& indices);

	Shader& GetShader();

public: // IRendering
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !MESH_H
