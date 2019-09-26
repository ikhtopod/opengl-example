#include "stdafx.h"

#define DPRINT(x) std::cout << #x << ": " << (x)
#define DPRINTL(x) DPRINT(x) << std::endl



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

	DPRINTL(GLVersion.major);
	DPRINTL(GLVersion.minor);

	// callbacks registration
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// mainloop
	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);

		Rendering();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
