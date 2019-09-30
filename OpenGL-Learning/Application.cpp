#include "stdafx.h"

#include "Application.h"


Application* Application::m_instance {};

void Application::InitInstance(Application* _this) {
	if (Application::m_instance == nullptr) {
		Application::m_instance = _this;
	}
}

Application::Application() {
	InitInstance(this);
}

Application* Application::GetInstance() {
	return Application::m_instance;
}

void Application::Run() {
	try {
		Init();
		Draw();
		Free();
	} catch (...) {

	}
}

void Application::Init() {}

void Application::Draw() {}

void Application::Free() {}
