#pragma once

#ifndef OPENGL_H
#define OPENGL_H

#include "Version.h"

class OpenGL final {
private:
	static constexpr Version DEFAULT_VERSION_OPENGL { 4, 6 };

private:
	static OpenGL* m_instance;
	static Version m_version;

private:
	OpenGL();

public:
	~OpenGL() = default;
	explicit OpenGL(const OpenGL&) = delete;
	explicit OpenGL(OpenGL&&) = delete;
	OpenGL& operator=(const OpenGL&) = delete;
	OpenGL& operator=(OpenGL&&) = delete;

public:
	static OpenGL* GetInstance();
	static Version GetVersion();

public:
	static void Init();
};

#endif // !OPENGL_H
