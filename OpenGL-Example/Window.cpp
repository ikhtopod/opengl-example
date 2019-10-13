#include "stdafx.h"
#include "Window.h"

const int Window::DEFAULT_SCREEN_SIZE = 768;

void Window::InitWindowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // MSAA
}

Window::Window() :
	m_context(nullptr), m_screenSize(DEFAULT_SCREEN_SIZE),
	m_title("OpenGL Example"), m_isVSync(GLFW_TRUE) {}

GLFWwindow* Window::GetContext() {
	return m_context;
}

const JustUtility::ScreenSize& Window::GetScreenSize() const {
	return m_screenSize;
}

const std::string& Window::GetTitle() const {
	return m_title;
}

void Window::InitCallbacks() const {
	glfwSetFramebufferSizeCallback(m_context, [](GLFWwindow* c, int w, int h) {
		Chatter::Say("width: ", w, "; height: ", h);
		glViewport(0, 0, w, h);
	});
}

/* IRendering */

void Window::Init() {
	if (glfwInit() == GLFW_FALSE) {
		throw std::exception { "GLFW not Init" };
	}

	Window::InitWindowHints();

	m_context = glfwCreateWindow(m_screenSize.width, m_screenSize.height, m_title.c_str(), nullptr, nullptr);
	if (m_context == nullptr) {
		glfwTerminate();
		throw std::exception { "GLFW not Init" };
	}

	glfwMakeContextCurrent(m_context);

	this->InitCallbacks();

	glfwSwapInterval(m_isVSync);
	glfwSetInputMode(m_context, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::Draw() {
	glfwSetWindowTitle(m_context, (m_title + " | time: " + std::to_string(glfwGetTime())).c_str());

	glfwSwapBuffers(m_context);
	glfwPollEvents();
}

void Window::Free() {
	if (this->m_context) {
		glfwDestroyWindow(this->m_context);
	}

	glfwTerminate();
}
