#pragma once

#ifndef MESH_H
#define MESH_H

#include "IRendering.h"
#include "Shader.h"

class Mesh : virtual public IRendering {
protected:
	static const GLsizei DEFAULT_BUFFER_SIZE;

	enum AttribIndex : GLuint {
		POSITION,
		// COLOR,
		NORMAL,
		TEXTURE,
	};

protected:
	GLenum m_mode = GL_TRIANGLES;

	std::vector<GLfloat> m_vertices {};
	std::vector<GLuint> m_indices {};

	GLuint vao {};
	GLuint vbo {};
	GLuint ebo {};

	Shader m_shader {};

protected:
	template <typename T>
	static void SetVector(const std::vector<T>& from, std::vector<T>& to) {
		to.clear();
		to.resize(from.size());
		std::copy(from.cbegin(), from.cend(), to.begin());
	}

	static void Unbind();

public:
	void SetVertices(const std::vector<GLfloat>& vertices);
	void SetIndices(const std::vector<GLuint>& indices);

public: // IRendering
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !MESH_H
