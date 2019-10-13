#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "Mesh.h"

class Renderer final {
private:
	Mesh m_triangleMesh {};

public:
	explicit Renderer();
	~Renderer();

	void Draw();
};

#endif // !RENDERER_H
