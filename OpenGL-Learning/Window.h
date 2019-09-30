#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "Triada.h"
#include "OpenGL.h"
#include "ScreenSize.h"

class Window final : public Triada {
private:
	static constexpr ScreenSize DEFAULT_WINDOW_SIZE { 800, 600 };

private:
	ScreenSize m_screenSize;
	std::string m_title;

	GLFWwindow* m_context;

private:
	void InitWindowHint();
	void CreateWindowObject();

public:
	Window();
	Window(const ScreenSize& size, const std::string& title);

public:
	GLFWwindow* GetContext();

	ScreenSize GetScreenSize();
	void SetScreenSize(const ScreenSize& screenSize);

public: // Triada
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !WINDOW_H
