#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "Triada.h"

class Window final : public Triada {
private:
	GLFWwindow* m_context;

private:
	void InitWindowHint();
	void CreateWindowObject();

public: // Triada
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !WINDOW_H
