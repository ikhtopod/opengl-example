#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer() {
	m_triangleMesh.SetVertices(
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		}
	);

	m_triangleMesh.GetShader().GetTexture().SetCoords(
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f,
		}
	);

	m_triangleMesh.SetIndices(
		{
			0, 1, 3,
			1, 2, 3,
		}
	);

	m_triangleMesh.Init();
}

Renderer::~Renderer() {
	m_triangleMesh.Free();
}

void Renderer::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_triangleMesh.Draw();
}
