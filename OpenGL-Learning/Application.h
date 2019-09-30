#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Triada.h"
#include "Window.h"

class Application final : public Triada {
private:
	static Application* m_instance;

private:
	Window m_window;
	Input m_input;

private:
	inline static void InitInstance(Application* _this);

private:
	Application();

public:
	~Application() = default;
	explicit Application(const Application&) = delete;
	explicit Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	static Application* GetInstance();
	void Run();

	void MainLoop();

public: // Triada
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !APPLICATION_H
