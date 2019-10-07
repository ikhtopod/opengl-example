#include "stdafx.h"

#include "Chatter.h"


#pragma region Structures

struct ScreenSize {
	int width = 0;
	int height = 0;
};

struct Color {
	GLfloat r = 0.0f;
	GLfloat g = 0.0f;
	GLfloat b = 0.0f;
	GLfloat a = 1.0f;
};

#pragma endregion

#pragma region Global

namespace {

ScreenSize g_screenSize { 800, 600 };
std::string g_title { "Just Title | Boo!" };
Color g_clearColor { .3f, .3f, .3f, 1.0f };
int g_isVSync = GLFW_TRUE;
int g_vSync = 60;

}

#pragma endregion

#pragma region Callbacks

void InitCallbacks(GLFWwindow* winContext) {
	glfwSetFramebufferSizeCallback(winContext, [](GLFWwindow* c, int w, int h) {
		Chatter::Say("width: ", w, "; height: ", h);
		g_screenSize.width = w;
		g_screenSize.height = h;
		glViewport(0, 0, w, h);
	});
}

#pragma endregion

#pragma region Input

void PressedEscapeForCloseWindow(GLFWwindow* winContext) {
	if (glfwGetKey(winContext, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(winContext, GLFW_TRUE);
		Chatter::Say("Key ESCAPE is Pressed. Current Window should close.");
	}
}

void ProcessInput(GLFWwindow* winContext) {
	PressedEscapeForCloseWindow(winContext);
}

#pragma endregion

#pragma region Init OpenGL

void InitOpenGL() {
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_PROGRAM_POINT_SIZE); // for glPointSize
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(g_clearColor.r, g_clearColor.g, g_clearColor.b, g_clearColor.a);
	glViewport(0, 0, g_screenSize.width, g_screenSize.height);
}

#pragma endregion

#pragma region Rendering

class IRendering {
protected:
	explicit IRendering(const IRendering&) = delete;
	explicit IRendering(IRendering&&) = delete;
	IRendering& operator=(const IRendering&) = delete;
	IRendering& operator=(IRendering&&) = delete;

	IRendering() = default;
	virtual ~IRendering() = default;

public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Free() = 0;
};

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
	void VertexErrorHandle() {
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

	void FragmentErrorHandle() {
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

	void ProgramErrorHandle() {
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

protected:
	void InitVertex() {
		m_vertex = glCreateShader(GL_VERTEX_SHADER);

		if (!m_vertex) {
			Chatter::Stink("Cannot create vertex shader");
			std::exit(EXIT_FAILURE);
		}

		glShaderSource(m_vertex, 1, &Shader::DEFAULT_VERTEX_SOURCE, nullptr);
		glCompileShader(m_vertex);

		VertexErrorHandle();
	}

	void InitFragment() {
		m_fragment = glCreateShader(GL_FRAGMENT_SHADER);

		if (!m_fragment) {
			Chatter::Stink("Cannot create fragment shader");
			std::exit(EXIT_FAILURE);
		}

		glShaderSource(m_fragment, 1, &Shader::DEFAULT_FRAGMENT_SOURCE, nullptr);
		glCompileShader(m_fragment);

		FragmentErrorHandle();
	}

	void InitProgram() {
		m_program = glCreateProgram();

		glAttachShader(m_program, m_vertex);
		glAttachShader(m_program, m_fragment);

		glLinkProgram(m_program);

		ProgramErrorHandle();
	}

protected:
	void UniformDemo() {
		static const GLchar* u_color { "u_color" };

		GLint u_colorLocation = glGetUniformLocation(m_program, u_color);
		GLfloat vec[] { .23f, .57f, .2f, 1.0f };

		glUniform4fv(u_colorLocation, 1, &vec[0]);
	}

public:	// IRendering
	virtual void Init() override {
		InitVertex();
		InitFragment();
		InitProgram();

		glDeleteShader(m_vertex);
		glDeleteShader(m_fragment);
	}

	virtual void Draw() override {
		glUseProgram(m_program);

		UniformDemo();
	}

	virtual void Free() override {
		glDeleteProgram(m_program);
	}
};

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

out vec4 FragColor;

void main() {
	FragColor = vec4(.23f, .57f, .2f, 1.0f);
}
)fs"
};

class Mesh : virtual public IRendering {
protected:
	static constexpr GLsizei DEFAULT_BUFFER_SIZE = 1;

	enum AttribIndex : GLuint {
		POSITION,
		NORMAL
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

	static void Unbind() {
		glBindVertexArray(0);
	}

public:
	void SetVertices(const std::vector<GLfloat>& vertices) {
		Mesh::SetVector<GLfloat>(vertices, m_vertices);
	}

	void SetIndices(const std::vector<GLuint>& indices) {
		Mesh::SetVector<GLuint>(indices, m_indices);
	}

public: // IRendering
	virtual void Init() override {
		glGenVertexArrays(Mesh::DEFAULT_BUFFER_SIZE, &vao);
		glGenBuffers(Mesh::DEFAULT_BUFFER_SIZE, &vbo);
		glGenBuffers(Mesh::DEFAULT_BUFFER_SIZE, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,
			static_cast<GLsizeiptr>(m_vertices.size()) * sizeof(GLfloat),
			&m_vertices[0], // or &(m_vertices)[0] for glm
			GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			static_cast<GLsizeiptr>(m_indices.size()) * sizeof(GLuint),
			&m_indices[0],
			GL_STATIC_DRAW);

		/* layouts */
		glEnableVertexAttribArray(Mesh::AttribIndex::POSITION);
		glVertexAttribPointer(Mesh::AttribIndex::POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));

		/* vertex normals example
		glEnableVertexAttribArray(MeshBase::AttribIndex::NORMAL);
		glVertexAttribPointer(MeshBase::AttribIndex::NORMAL, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, normal)); */

		Mesh::Unbind();

		m_shader.Init();
	}

	virtual void Draw() override {
		m_shader.Draw();

		glBindVertexArray(vao);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(m_mode, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
		Mesh::Unbind();
	}

	virtual void Free() override {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);

		m_shader.Free();
	}
};

class Renderer final {
private:
	Mesh m_triangleMesh {};

public:
	Renderer() {
		m_triangleMesh.SetVertices(
			{
				 0.5f,  0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f,
			}
		);

		m_triangleMesh.SetIndices(
			{
				0, 1, 3,
				1, 2, 3,
			}
		);

		m_triangleMesh.Init();
	}

	~Renderer() {
		m_triangleMesh.Free();
	}

	void Draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_triangleMesh.Draw();
	}
};

#pragma endregion

#pragma region Main

int main() {
	if (glfwInit() == GLFW_FALSE) {
		Chatter::Stink("GLFW not Init");
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // MSAA

	GLFWwindow* winContext = glfwCreateWindow(g_screenSize.width, g_screenSize.height, g_title.c_str(), nullptr, nullptr);
	if (winContext == nullptr) {
		Chatter::Stink("Window not created");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(winContext);
	InitCallbacks(winContext);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Chatter::Stink("OpenGl not loaded");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSwapInterval(g_isVSync);
	glfwSetInputMode(winContext, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	InitOpenGL();

	for (Renderer renderer {}; !glfwWindowShouldClose(winContext); ) {
		glfwSetWindowTitle(winContext, (g_title + " | time: " + std::to_string(glfwGetTime())).c_str());

		ProcessInput(winContext);

		renderer.Draw();

		glfwSwapBuffers(winContext);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

#pragma endregion
