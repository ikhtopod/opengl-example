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
	stbi_set_flip_vertically_on_load(m_stb_flipVertical);

	uint8_t* data = stbi_load(DEFAULT_IMAGE_PATH.c_str(),
		&m_stb_width, &m_stb_height, &m_stb_nrChannels,
		static_cast<int>(m_stb_componentsPerPixel));

	if (data) {
		// use image
		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RGBA, m_stb_width, m_stb_height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	} else {
		const char* message { "Failed to load texture" };
		Chatter::Stink(message);
		throw std::exception { message };
	}

	Unbind();
}

void Texture::Draw() {
	glActiveTexture(tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);
}

void Texture::Free() {
	glDeleteTextures(1, &tex1);
}
