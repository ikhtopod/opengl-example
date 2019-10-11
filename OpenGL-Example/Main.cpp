#include "stdafx.h"

#include "Chatter.h"
#include "Window.h"
#include "Mesh.h"

#pragma region Global

namespace {

using namespace JustUtility;

Color g_clearColor { .3f, .3f, .3f, 1.0f };
Window g_window {};

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

#pragma region OpenGL

void LoadOpenGL() {
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Chatter::Stink("OpenGL not loaded");
		glfwTerminate();
		throw std::exception { Chatter::c_LastStink() };
	}
}

void InitOpenGL() {
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_PROGRAM_POINT_SIZE); // for glPointSize
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(g_clearColor.r, g_clearColor.g, g_clearColor.b, g_clearColor.a);
	glViewport(0, 0, g_window.GetScreenSize().width, g_window.GetScreenSize().height);
}

#pragma endregion

#pragma region Rendering

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

		m_triangleMesh.GetShader().GetTexture().SetCoords(
			{
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,
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
	g_window.Init();

	LoadOpenGL();
	InitOpenGL();

	for (Renderer renderer {}; !glfwWindowShouldClose(g_window.GetContext()); ) {
		g_window.Draw();
		ProcessInput(g_window.GetContext());
		renderer.Draw();
	}

	g_window.Free();
	return EXIT_SUCCESS;
}

#pragma endregion
