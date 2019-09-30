#include "stdafx.h"
#include "Input.h"

void Input::CallbacksRegistration() {
	GLFWwindow* context = Application::GetInstance()->GetWindow().GetContext();
	//glfwSetFramebufferSizeCallback(context, FramebufferSizeCallback);
}

void Input::Init() {
	CallbacksRegistration();
}

void Input::Draw() {
	glfwPollEvents();
}

void Input::Free() {}
