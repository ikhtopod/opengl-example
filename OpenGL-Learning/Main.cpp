#include "stdafx.h"

#include "Chatter.h"


void SetFramebufferSizeCallback(GLFWwindow* winContext, int width, int height) {
	glViewport(0, 0, width, height);
}

void PressedEscapeForCloseWindow(GLFWwindow* winContext) {
	if (glfwGetKey(winContext, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(winContext, GLFW_TRUE);
	}
}

void ProcessInput(GLFWwindow* winContext) {
	PressedEscapeForCloseWindow(winContext);
}

int main(int argc, char** argv) {
	if (glfwInit() == GLFW_FALSE) {
		Chatter::Stink("GLFW not init");
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* winContext = glfwCreateWindow(800, 600, "Fock Yo!", nullptr, nullptr);
	if (winContext == nullptr) {
		Chatter::Stink("GLFW", "window", "context", "is not", "created");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(winContext);
	glfwSetFramebufferSizeCallback(winContext, SetFramebufferSizeCallback);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Chatter::Stink("Cannot load OpenGL");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glClearColor(.75f, .75f, .75f, 1.0f);

	while (!glfwWindowShouldClose(winContext)) {
		ProcessInput(winContext);

		Chatter::Say("There should be a triangle.");

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(winContext);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
