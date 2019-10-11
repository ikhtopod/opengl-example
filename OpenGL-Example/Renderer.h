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

	void Draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_triangleMesh.Draw();
	}
};

#endif // !RENDERER_H
