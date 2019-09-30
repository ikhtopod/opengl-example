#pragma once

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
