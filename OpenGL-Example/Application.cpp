#include "stdafx.h"
#include "Application.h"


void Application::Run() {
	this->Init();
	this->Draw();
	this->Free();
}

void Application::LoadOpenGL() {
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		Chatter::Stink("OpenGL not loaded");
		glfwTerminate();
		throw std::exception { Chatter::c_LastStink() };
	}
}

void Application::InitOpenGL() const {
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_PROGRAM_POINT_SIZE); // for glPointSize
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glViewport(0, 0, m_window.GetScreenSize().width, m_window.GetScreenSize().height);
}

void Application::MainLoop() {
	TestRenderer testRenderer {};

	while (!glfwWindowShouldClose(m_window.GetContext())) {
		m_window.Draw();
		ProcessInput();
		testRenderer.Draw();
	}
}

/* Input */

void Application::ProcessInput() {
	PressEscapeForCloseWindow();
}

void Application::PressEscapeForCloseWindow() {
	if (glfwGetKey(m_window.GetContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window.GetContext(), GLFW_TRUE);
		Chatter::Say("Key ESCAPE is Pressed. Current Window should close.");
	}
}

/* IRendering */

void Application::Init() {
	m_window.Init();

	LoadOpenGL();
	InitOpenGL();
}

void Application::Draw() {
	this->MainLoop();
}

void Application::Free() {
	m_window.Free();
}
