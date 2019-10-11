#pragma once

#ifndef JUSTUTILITY_H
#define JUSTUTILITY_H

namespace JustUtility {

#pragma region Structures

struct ScreenSize {
	int width = 0;
	int height = 0;

	explicit ScreenSize(int x);
	explicit ScreenSize(int w, int h);
};

struct Color {
	GLfloat r = 0.0f;
	GLfloat g = 0.0f;
	GLfloat b = 0.0f;
	GLfloat a = 1.0f;

	explicit Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
};

#pragma endregion

enum AttribIndex : GLuint {
	POSITION,
	TEXTURE,
};

template <typename T>
static void CopyVector(const std::vector<T>& from, std::vector<T>& to) {
	to.clear();
	to.resize(from.size());
	std::copy(from.cbegin(), from.cend(), to.begin());
}

} // namespace JustUtility

#endif // !JUSTUTILITY_H
