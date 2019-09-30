#include "stdafx.h"
#include "OpenGL.h"

OpenGL* OpenGL::m_instance = nullptr;
Version OpenGL::m_version = OpenGL::DEFAULT_VERSION_OPENGL;

OpenGL::OpenGL() {
	if (OpenGL::m_instance == nullptr) {
		OpenGL::m_instance = this;
	}
}

OpenGL* OpenGL::GetInstance() {
	return OpenGL::m_instance;
}

Version OpenGL::GetVersion() {
	return m_version;
}

void OpenGL::Init() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::exception { "Failed to initialize GLAD" };
	}
}
