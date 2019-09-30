#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

class Application final {
private:
	static Application* m_instance;

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
};

#endif // !APPLICATION_H
