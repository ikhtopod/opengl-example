#include "stdafx.h"
#include "Application.h"

Application* Application::m_instance = nullptr;

Application::Application() : m_window(ScreenSize { 800, 600 }, "3D Example"), m_input() {
	if (Application::m_instance == nullptr) {
		Application::m_instance = this;
	}
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

Window& Application::GetWindow() {
	return m_window;
}

void Application::Init() {
	m_window.Init();
	m_input.Init();
}

void Application::MainLoop() {
	m_window.Draw();
	m_input.Draw();
}

void Application::Draw() {
	MainLoop();
}

void Application::Free() {
	m_window.Free();
	m_input.Free();
}
