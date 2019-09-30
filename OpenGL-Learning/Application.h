#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Triada.h"
#include "ScreenSize.h"
#include "Window.h"
#include "Input.h"

class Application final : public Triada {
private:
	static Application* m_instance;

private:
	Window m_window;
	Input m_input;

private:
	Application();

private:
	void MainLoop();

public:
	~Application() = default;
	explicit Application(const Application&) = delete;
	explicit Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	static Application* GetInstance();
	void Run();

public:
	Window& GetWindow();

public: // Triada
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !APPLICATION_H
