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
Color g_clearColor { .75f, .75f, .75f, 1.0f };
int g_isVSync = GLFW_TRUE;
int g_vSync = 60;

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
	glFrontFace(GL_CCW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(g_clearColor.r, g_clearColor.g, g_clearColor.b, g_clearColor.a);
	glViewport(0, 0, g_screenSize.width, g_screenSize.height);
}

#pragma endregion

#pragma region Rendering

void Rendering(GLFWwindow* winContext) {
	// There should be a triangle.
}

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

	glfwSetFramebufferSizeCallback(winContext, [](GLFWwindow* c, int w, int h) {
		Chatter::Say("width: ", w, "; height: ", h);
		g_screenSize.width = w;
		g_screenSize.height = h;
		glViewport(0, 0, w, h);
	});

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Chatter::Stink("OpenGl not loaded");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSwapInterval(g_isVSync);
	glfwSetInputMode(winContext, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	InitOpenGL();

	while (!glfwWindowShouldClose(winContext)) {
		glfwSetWindowTitle(winContext, (g_title + " | time: " + std::to_string(glfwGetTime())).c_str());

		ProcessInput(winContext);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Rendering(winContext);

		glfwSwapBuffers(winContext);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

#pragma endregion
