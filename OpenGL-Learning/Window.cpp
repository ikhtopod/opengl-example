#include "stdafx.h"
#include "Window.h"

void Window::InitWindowHint() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGL::version.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGL::version.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS
}

void Window::CreateWindowObject() {
	if (m_context) return;

	m_context = glfwCreateWindow(Screen::size.width, Screen::size.height, Screen::title.c_str(), nullptr, nullptr);

	if (m_context == nullptr) {
		Free();
		throw std::exception { "Failed to create glfw window" };
	}

	glfwMakeContextCurrent(m_context);
}

void Window::Init() {
	if (glfwInit() == GLFW_FALSE) {
		throw std::exception { "glfw not init" };
	}

	InitWindowHint();
	CreateWindowObject();



}

void Window::Draw() {
	glfwSwapBuffers(m_context);
}

void Window::Free() {
	glfwTerminate();
}
