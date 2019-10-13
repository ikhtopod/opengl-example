#include "stdafx.h"
#include "Shader.h"


const GLchar* Shader::DEFAULT_VERTEX_SOURCE {
R"vs(#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main() {
	gl_Position = projection * view * model * vec4(a_position, 1.0);
	TexCoord = a_texture;
}
)vs"
};

const GLchar* Shader::DEFAULT_FRAGMENT_SOURCE {
R"fs(#version 460 core

uniform float u_time;
uniform vec4 u_color;

in vec2 TexCoord;

layout (binding = 0) uniform sampler2D u_texture1;

void main() {
	gl_FragColor = texture(u_texture1, TexCoord);
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
		throw std::exception { Chatter::c_LastStink() };
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
		throw std::exception { Chatter::c_LastStink() };
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
		throw std::exception { Chatter::c_LastStink() };
	}
}

void Shader::InitVertex() {
	m_vertex = glCreateShader(GL_VERTEX_SHADER);

	if (!m_vertex) {
		Chatter::Stink("Cannot create vertex shader");
		throw std::exception { Chatter::c_LastStink() };
	}

	glShaderSource(m_vertex, 1, &Shader::DEFAULT_VERTEX_SOURCE, nullptr);
	glCompileShader(m_vertex);

	VertexErrorHandle();
}

void Shader::InitFragment() {
	m_fragment = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_fragment) {
		Chatter::Stink("Cannot create fragment shader");
		throw std::exception { Chatter::c_LastStink() };
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

	// model view projection example
	glm::mat4 model { 1.0f };
	glm::mat4 view { 1.0f };
	glm::mat4 projection { 1.0f };

	GLfloat degrees = JustUtility::Repeat(
		static_cast<float>(glfwGetTime()) * 60.0f,
		0.0f, 360.0f);

	model = glm::rotate(model, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	GLint u_modelLocation = glGetUniformLocation(m_program, "model");
	GLint u_viewLocation = glGetUniformLocation(m_program, "view");
	GLint u_projectionLocation = glGetUniformLocation(m_program, "projection");

	glUniformMatrix4fv(u_modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(u_viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(u_projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

Texture& Shader::GetTexture() {
	return m_texture;
}

/* IRendering */

void Shader::Init() {
	m_texture.Init();

	InitVertex();
	InitFragment();
	InitProgram();

	glDeleteShader(m_vertex);
	glDeleteShader(m_fragment);
}

void Shader::Draw() {
	m_texture.Draw();

	glUseProgram(m_program);

	UniformDemo();
}

void Shader::Free() {
	m_texture.Free();

	glDeleteProgram(m_program);
}
