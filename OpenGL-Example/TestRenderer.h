#pragma once

#ifndef TESTRENDERER_H
#define TESTRENDERER_H

#include "BaseRenderer.h"
#include "Mesh.h"

class TestRenderer final : public BaseRenderer {
private:
	Mesh m_triangleMesh {};

public:
	explicit TestRenderer();
	~TestRenderer();

public: // BaseRenderer
	virtual void Draw() override;
};

#endif // !TESTRENDERER_H
