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
	using CoordType = glm::vec2;

private:
	static const std::string DEFAULT_IMAGE_PATH;

private:
	std::vector<CoordType> m_coords {};

	GLuint vbo {};
	GLuint tex1 {};

private:
	static void Unbind();

public:
	void SetCoords(const std::vector<CoordType>& coords);

public: // IRendering
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !TEXTURE_H
