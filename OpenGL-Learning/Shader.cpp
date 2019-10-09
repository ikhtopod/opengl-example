#include "stdafx.h"
#include "Shader.h"


const GLchar* Shader::DEFAULT_VERTEX_SOURCE {
R"vs(#version 460 core

layout (location = 0) in vec3 m_vertices;

void main() {
	gl_Position = vec4(m_vertices, 1.0);
}
)vs"
};

const GLchar* Shader::DEFAULT_FRAGMENT_SOURCE {
R"fs(#version 460 core

uniform float u_time;
uniform vec4 u_color;

//out vec4 FragColor;

void main() {
	gl_FragColor = u_color * abs(sin(u_time)); // wave color
}
)fs"
};

void Shader::VertexErrorHandle() {
	GLint successCompileVertex {};
	glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &successCompileVertex);

	if (successCompileVertex == GL_FALSE) {
		GLint infoLogLength {};
		glGetShaderiv(m_vertex, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength != 0) {
			GLchar* infoLog = new GLchar[infoLogLength];

			/*
				written - целочисленная переменная, в которую
				будет записано фактическое число символов
				(без учета заключительного нулевого символа),
				скопированных в буфер (infoLog).
				Вместо written можно указать nullptr.
			*/
			GLsizei written {};
			glGetShaderInfoLog(m_vertex, infoLogLength, &written, infoLog);
			Chatter::Stink("vertex shader compilation failed:", infoLog);

			delete[] infoLog;
		}

		glDeleteShader(m_vertex);

		Chatter::Stink("Cannot compile vertex shader");
		std::exit(EXIT_FAILURE);
	}
}

void Shader::FragmentErrorHandle() {
	GLint successCompileFragment {};
	glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &successCompileFragment);

	if (successCompileFragment == GL_FALSE) {
		GLint infoLogLength {};
		glGetShaderiv(m_fragment, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength != 0) {
			GLchar* infoLog = new GLchar[infoLogLength];

			GLsizei written {};
			glGetShaderInfoLog(m_fragment, infoLogLength, &written, infoLog);
			Chatter::Stink("fragment shader compilation failed:", infoLog);

			delete[] infoLog;
		}

		glDeleteShader(m_vertex);
		glDeleteShader(m_fragment);

		Chatter::Stink("Cannot compile fragment shader");
		std::exit(EXIT_FAILURE);
	}
}

void Shader::ProgramErrorHandle() {
	GLint successLinkProgram {};
	glGetProgramiv(m_program, GL_LINK_STATUS, &successLinkProgram);

	if (successLinkProgram == GL_FALSE) {
		GLint infoLogLength {};
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength != 0) {
			GLchar* infoLog = new GLchar[infoLogLength];

			GLsizei written {};
			glGetProgramInfoLog(m_program, infoLogLength, &written, infoLog);
			Chatter::Stink("link program failed:", infoLog);

			delete[] infoLog;
		}

		glDeleteShader(m_vertex);
		glDeleteShader(m_fragment);
		glDeleteProgram(m_program);

		Chatter::Stink("Cannot link program");
		std::exit(EXIT_FAILURE);
	}
}

void Shader::InitVertex() {
	m_vertex = glCreateShader(GL_VERTEX_SHADER);

	if (!m_vertex) {
		Chatter::Stink("Cannot create vertex shader");
		std::exit(EXIT_FAILURE);
	}

	glShaderSource(m_vertex, 1, &Shader::DEFAULT_VERTEX_SOURCE, nullptr);
	glCompileShader(m_vertex);

	VertexErrorHandle();
}

void Shader::InitFragment() {
	m_fragment = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_fragment) {
		Chatter::Stink("Cannot create fragment shader");
		std::exit(EXIT_FAILURE);
	}

	glShaderSource(m_fragment, 1, &Shader::DEFAULT_FRAGMENT_SOURCE, nullptr);
	glCompileShader(m_fragment);

	FragmentErrorHandle();
}

void Shader::InitProgram() {
	m_program = glCreateProgram();

	glAttachShader(m_program, m_vertex);
	glAttachShader(m_program, m_fragment);

	glLinkProgram(m_program);

	ProgramErrorHandle();
}

void Shader::UniformDemo() {
	static const GLchar* u_color { "u_color" };
	static const GLchar* u_time { "u_time" };

	GLint u_colorLocation = glGetUniformLocation(m_program, u_color);
	GLint u_timeLocation = glGetUniformLocation(m_program, u_time);
	GLfloat vec[] { .23f, .57f, .2f, 1.0f };
	GLfloat time = static_cast<GLfloat>(glfwGetTime());

	glUniform1f(u_timeLocation, time);
	glUniform4fv(u_colorLocation, 1, &vec[0]);
}

/* IRendering */

void Shader::Init() {
	InitVertex();
	InitFragment();
	InitProgram();

	glDeleteShader(m_vertex);
	glDeleteShader(m_fragment);
}

void Shader::Draw() {
	glUseProgram(m_program);

	UniformDemo();
}

void Shader::Free() {
	glDeleteProgram(m_program);
}
