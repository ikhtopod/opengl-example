#include "stdafx.h"
#include "JustUtility.h"

namespace JustUtility {

ScreenSize::ScreenSize(int x) :
	width(x), height(x) {}

ScreenSize::ScreenSize(int w, int h) :
	width(w), height(h) {}

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :
	r(r), g(g), b(b), a(a) {}

float Repeat(float value, float min_value, float max_value) {
	return min_value + std::fmodf(value, max_value);
}

} // namespace JustUtility
