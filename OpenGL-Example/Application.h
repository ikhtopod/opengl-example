#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include "IRendering.h"
#include "Renderer.h"
#include "Window.h"

class Application final : public IRendering {
private:
	JustUtility::Color m_clearColor { .3f, .3f, .3f, 1.0f };

	Window m_window {};

private: // OpenGL
	static void LoadOpenGL();
	void InitOpenGL() const;

private:
	void MainLoop();

private: // Input
	void ProcessInput();

	void PressEscapeForCloseWindow();

public: // Run
	void Run();

private: // IRendering
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !APPLICATION_H
