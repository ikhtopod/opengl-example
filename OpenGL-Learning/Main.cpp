#include "stdafx.h"

#include "Chatter.h"

/*void SetFramebufferSize(GLFWwindow* winContext, int w, int h) {
	Chatter::Say("width: ", w, "; height: ", h);
	glViewport(0, 0, w, h);
}*/

void PressedEscapeForCloseWindow(GLFWwindow* winContext) {
	if (glfwGetKey(winContext, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(winContext, GLFW_TRUE);
		Chatter::Say("Key ESCAPE is Pressed. Current Window should close.");
	}
}

void ProcessInput(GLFWwindow* winContext) {
	PressedEscapeForCloseWindow(winContext);
}

int main(int argc, char** argv) {
	if (glfwInit() == GLFW_FALSE) {
		Chatter::Stink("GLFW not Init");
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* winContext = glfwCreateWindow(800, 600, "Just Title | Boo!", nullptr, nullptr);
	if (winContext == nullptr) {
		Chatter::Stink("Window not created");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(winContext);
	// glfwSetFramebufferSizeCallback(winContext, SetFramebufferSize);
	glfwSetFramebufferSizeCallback(winContext, [](GLFWwindow* c, int w, int h) {
		Chatter::Say("width: ", w, "; height: ", h);
		glViewport(0, 0, w, h);
	});

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Chatter::Stink("");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glClearColor(.75f, .75f, .75f, 1.0f);
	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(winContext)) {
		ProcessInput(winContext);

		glClear(GL_COLOR_BUFFER_BIT);
		// There should be a triangle.

		glfwSwapBuffers(winContext);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
