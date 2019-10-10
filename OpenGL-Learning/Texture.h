#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "IRendering.h"
#include "Chatter.h"

enum class TextureComponent : int {
	NONE,			///< 0: default
	GREY,			///< 1: grey
	GREY_ALPHA,		///< 2: grey, alpha
	RGB,			///< 3: red, green, blue
	RGBA			///< 4: red, green, blue, alpha
};

class Texture final : public IRendering {
private:
	static const std::string DEFAULT_IMAGE_PATH;

private:
	std::vector<GLfloat> m_coords {};

	GLuint vbo {};
	GLuint tex1 {};

	int m_stb_width = 0;
	int m_stb_height = 0;
	int m_stb_nrChannels = 0;

	bool m_stb_flipVertical = true;

	TextureComponent m_stb_componentsPerPixel = TextureComponent::RGBA;

private:
	static void Unbind();

public:
	void SetCoords(const std::vector<GLfloat>& coords);

public: // IRendering
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !TEXTURE_H
