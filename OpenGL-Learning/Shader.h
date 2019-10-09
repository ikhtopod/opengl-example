#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "IRendering.h"
#include "Chatter.h"

class Shader : virtual public IRendering {
protected:
	static const GLchar* DEFAULT_VERTEX_SOURCE;
	static const GLchar* DEFAULT_FRAGMENT_SOURCE;

protected:
	GLuint m_vertex {};
	// GLuint m_geometry {};
	GLuint m_fragment {};
	GLuint m_program {};

private: // Error Handle
	void VertexErrorHandle();
	void FragmentErrorHandle();
	void ProgramErrorHandle();

protected:
	void InitVertex();
	void InitFragment();
	void InitProgram();

protected:
	void UniformDemo();

public:	// IRendering
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !SHADER_H
