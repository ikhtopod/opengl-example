#include "stdafx.h"

#define DPRINT(x) std::cout << #x << ": " << (x)
#define DPRINTL(x) DPRINT(x) << std::endl


void ShowOpenGLVersion_Example_1() {
	DPRINTL(GLVersion.major);
	DPRINTL(GLVersion.minor);
}

void ShowOpenGLVersion_Example_2() {
	GLint versionMajor, versionMinor;

	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

	DPRINTL(versionMajor);
	DPRINTL(versionMinor);
}

void ShowOpenGLInfo() {
	//ShowOpenGLVersion_Example_1();
	ShowOpenGLVersion_Example_2();

	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

struct ScreenSize {
	GLsizei width = 0;
	GLsizei height = 0;
};

class Screen {
public:
	static ScreenSize size;
	static std::string title;
};

ScreenSize Screen::size { 800, 600 };
std::string Screen::title { "OpenGL Window" };



struct Version {
	int major = 0;
	int minor = 0;
};

class OpenGL {
public:
	static Version version;
};

Version OpenGL::version { 4, 6 };


/* Begin GLFW Callbacks */

// Viewport size
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	Screen::size.width = width;
	Screen::size.height = height;

	glViewport(0, 0, Screen::size.width, Screen::size.height);
}

/* End GLFW Callbacks */


/* Begin Inputs */

// Close Application
void CloseApplicationInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

// Run all inputs
void ProcessInput(GLFWwindow* window) {
	CloseApplicationInput(window);
}

/* End Inputs */


/* Begin Rendering */

void ClearColor() {
	glClearColor(.75f, .75f, .75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Rendering() {
	ClearColor();
}

/* End Rendering */


/* Begin Shader */

std::string vert { R"vs(#version 460 core

layout (location = 0) in vec3 pos;

void main(){
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
}
)vs" };

std::string frag { R"fs(#version 460 core

out vec4 FragColor;

void main(){
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)fs" };

/* End Shader */

constexpr GLfloat UNIT = 1.0f;

void NormalizeVerticesToUnit(std::vector<GLfloat>& v) {
	std::transform(v.begin(), v.end(), v.begin(), [](GLfloat v) { return v * UNIT; });
}

int main() {
	// init glfw
	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "glfw not init" << std::endl;
		return EXIT_FAILURE;
	}

	// OpenGL settings for glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGL::version.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGL::version.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS

	// create window object
	GLFWwindow* window = glfwCreateWindow(Screen::size.width, Screen::size.height, Screen::title.c_str(), nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	ShowOpenGLInfo();

	// callbacks registration
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// VERTICES
	std::vector<GLfloat> vertices {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,  // top left 
	};
	NormalizeVerticesToUnit(vertices);

	std::vector<GLuint> indices {
		0, 1, 3,  // first triangle
		1, 2, 3,  // second triangle
	};

	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);


	// INIT VERTEX CODE
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	// vertex normals
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// glBindVertexArray(0); // not need to unbind it every time

	// VERTEX SHADER
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	if (vertexShader == 0) {
		std::cout << "Error: vertexShader == 0" << std::endl;
		return 0;
	}

	const GLchar* vShaderSource = vert.c_str();
	glShaderSource(vertexShader, 1, &vShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLint successCompileVertex {};
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successCompileVertex);

	if (!successCompileVertex) {
		GLint infoLogLength {};
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0) {
			GLchar* infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(vertexShader, infoLogLength, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			delete[] infoLog;
		}

		glDeleteShader(vertexShader);
		return 0;
	}

	// FRAGMENT SHADER
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	if (fragmentShader == 0) {
		std::cout << "Error: fragmentShader == 0" << std::endl;
		return 0;
	}

	const GLchar* fShaderSource = frag.c_str();
	glShaderSource(fragmentShader, 1, &fShaderSource, nullptr);
	glCompileShader(fragmentShader);

	GLint successCompileFragment {};
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successCompileFragment);

	if (!successCompileFragment) {
		GLint infoLogLength {};
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0) {
			GLchar* infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(fragmentShader, infoLogLength, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			delete[] infoLog;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return 0;
	}

	// SHADER PROGRAM
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint successLinkProgram {};
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successLinkProgram);

	if (!successLinkProgram) {
		GLint infoLogLength {};
		glGetProgramiv(successLinkProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0) {
			GLchar* infoLog = new GLchar[infoLogLength];
			glGetProgramInfoLog(shaderProgram, infoLogLength, nullptr, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
			delete[] infoLog;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// mainloop
	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);

		// Rendering();
		ClearColor();

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(0); // unbind

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return EXIT_SUCCESS;
}
