#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "Triada.h"
#include "Application.h"

/*void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	Application::GetInstance()->GetWindow().SetScreenSize(ScreenSize { width, height });
	glViewport(0, 0, width, height);
}*/

class Input final : public Triada {
public:
	void CallbacksRegistration();

public: // Triada
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !INPUT_H
