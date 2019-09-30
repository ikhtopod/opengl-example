#include "stdafx.h"
#include "Window.h"

Window::Window() : Window(Window::DEFAULT_WINDOW_SIZE, "No Title") {}

Window::Window(const ScreenSize& size, const std::string& title) :
	m_screenSize(size), m_title(title), m_context(nullptr) {}

GLFWwindow* Window::GetContext() {
	return m_context;
}

ScreenSize Window::GetScreenSize() {
	return m_screenSize;
}

void Window::SetScreenSize(const ScreenSize& screenSize) {
	m_screenSize = screenSize;
}

void Window::InitWindowHint() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGL::GetVersion().major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGL::GetVersion().minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS
}

void Window::CreateWindowObject() {
	if (m_context) return;

	m_context = glfwCreateWindow(m_screenSize.width, m_screenSize.height, m_title.c_str(), nullptr, nullptr);

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

	try {
		OpenGL::GetInstance()->Init();
	} catch (...) {
		Free();
		throw;
	}
}

void Window::Draw() {
	glfwSwapBuffers(m_context);
}

void Window::Free() {
	glfwTerminate();
}
