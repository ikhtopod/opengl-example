#include "stdafx.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

const std::string Texture::DEFAULT_IMAGE_PATH { R"(..\Images\InsolentEngine.png)" };

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetCoords(const std::vector<GLfloat>& coords) {
	JustUtility::CopyVector<GLfloat>(coords, m_coords);
}

/* IRendering */

void Texture::Init() {
	/* load vertex */
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		static_cast<GLsizeiptr>(m_coords.size()) * sizeof(GLfloat),
		&m_coords[0],
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(JustUtility::AttribIndex::TEXTURE);
	glVertexAttribPointer(JustUtility::AttribIndex::TEXTURE, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void*>(0));

	/* init texture */

	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image
	const int FLIP_VERTICAL = 1;
	stbi_set_flip_vertically_on_load(FLIP_VERTICAL);

	int width = 0;
	int height = 0;
	int nrChannels = 0;
	TextureComponent componentsPerPixel { TextureComponent::RGBA };

	uint8_t* data = stbi_load(DEFAULT_IMAGE_PATH.c_str(),
		&width, &height, &nrChannels,
		static_cast<int>(componentsPerPixel));

	if (data) {
		// use image
		const GLsizei LEVELS = 1;
		glTexStorage2D(GL_TEXTURE_2D, LEVELS, GL_RGBA8, width, height);

		const GLint LEVEL = 0;
		const GLint XOFFSET = 0;
		const GLint YOFFSET = 0;
		glTexSubImage2D(GL_TEXTURE_2D, LEVEL,
			XOFFSET, YOFFSET, width, height,
			GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	} else {
		Chatter::Stink("Failed to load texture");
		throw std::exception { Chatter::c_LastStink() };
	}

	Unbind();
}

void Texture::Draw() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1);
}

void Texture::Free() {
	glDeleteTextures(1, &tex1);
}
