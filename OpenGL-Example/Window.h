#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "Chatter.h"
#include "IRendering.h"

class Window final : public IRendering {
private:
	static const int DEFAULT_SCREEN_SIZE;

private:
	GLFWwindow* m_context;
	JustUtility::ScreenSize m_screenSize;
	std::string m_title;
	int m_isVSync = GLFW_TRUE;

private:
	static void InitWindowHints();

private:
	void InitCallbacks() const;

public:
	explicit Window();

public:
	GLFWwindow* GetContext();
	const JustUtility::ScreenSize& GetScreenSize() const;
	const std::string& GetTitle() const;

public: // IRendering
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !WINDOW_H
