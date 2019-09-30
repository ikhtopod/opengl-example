#include "stdafx.h"

#define DPRINT(x) std::cout << #x << ": " << (x)
#define DPRINTL(x) DPRINT(x) << std::endl


#define SHOW_INFO_STRING(type) std::cout << #type << ": " << glGetString(type) << std::endl

#define SHOW_INFO_INT(type) { \
	GLint x {}; \
	glGetIntegerv(type, &x); \
	std::cout << #type << ": " << x << std::endl; \
}

void ShowOpenGLInfo() {
	SHOW_INFO_INT(GL_MAJOR_VERSION);
	SHOW_INFO_INT(GL_MINOR_VERSION);

	SHOW_INFO_STRING(GL_VENDOR);
	SHOW_INFO_STRING(GL_RENDERER);
	SHOW_INFO_STRING(GL_VERSION);

	SHOW_INFO_INT(GL_MAX_VERTEX_ATTRIBS);
}

struct ScreenSize_Example {
	GLsizei width = 0;
	GLsizei height = 0;
};

class Screen_Example {
public:
	static ScreenSize_Example size;
	static std::string title;
};

ScreenSize_Example Screen_Example::size { 800, 600 };
std::string Screen_Example::title { "OpenGL Window" };



struct Version_Example {
	int major = 0;
	int minor = 0;
};

class OpenGL_Example {
public:
	static Version_Example version;
};

Version_Example OpenGL_Example::version { 4, 6 };


/* Begin GLFW Callbacks */

// Viewport size
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	Screen_Example::size.width = width;
	Screen_Example::size.height = height;

	glViewport(0, 0, Screen_Example::size.width, Screen_Example::size.height);
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

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
  
out vec3 ourColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}    
)vs" };

std::string frag { R"fs(#version 460 core

out vec4 FragColor;  
in vec3 ourColor;
  
void main() {
    FragColor = vec4(ourColor, 1.0);
}
)fs" };

/* End Shader */

constexpr GLfloat UNIT = 1.0f;

void NormalizeVerticesToUnit(std::vector<GLfloat>& v) {
	std::transform(v.begin(), v.end(), v.begin(), [](GLfloat v) { return v * UNIT; });
}

int _main() {
	// init glfw
	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "glfw not init" << std::endl;
		return EXIT_FAILURE;
	}

	// OpenGL_Example settings for glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGL_Example::version.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGL_Example::version.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS

	// create window object
	GLFWwindow* window = glfwCreateWindow(Screen_Example::size.width, Screen_Example::size.height, Screen_Example::title.c_str(), nullptr, nullptr);
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
		 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 // positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
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

	// positions attribute
	GLuint positionAttributeIndex = 0;
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(positionAttributeIndex);

	// color attribute
	GLuint colorAttributeIndex = positionAttributeIndex + 1;
	glVertexAttribPointer(colorAttributeIndex, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colorAttributeIndex);

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

	if (successCompileVertex == GL_FALSE) {
		GLint infoLogLength {};
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0) {
			GLchar* infoLog = new GLchar[infoLogLength];

			/*
				written - целочисленная переменная, в которую
				будет записано фактическое число символов
				(без учета заключительного нулевого символа),
				скопированных в буфер (infoLog).
			*/
			GLsizei written {};
			glGetShaderInfoLog(vertexShader, infoLogLength, &written, infoLog);
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

	if (successCompileFragment == GL_FALSE) {
		GLint infoLogLength {};
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0) {
			GLchar* infoLog = new GLchar[infoLogLength];

			GLsizei written {};
			glGetShaderInfoLog(fragmentShader, infoLogLength, &written, infoLog);
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

	if (successLinkProgram == GL_FALSE) {
		GLint infoLogLength {};
		glGetProgramiv(successLinkProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0) {
			GLchar* infoLog = new GLchar[infoLogLength];

			GLsizei written {};
			glGetProgramInfoLog(shaderProgram, infoLogLength, &written, infoLog);
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

		float timeValue = static_cast<float>(glfwGetTime());
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

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
