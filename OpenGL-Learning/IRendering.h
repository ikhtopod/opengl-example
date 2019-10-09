#pragma once

#ifndef IRENDERING_H
#define IRENDERING_H

class IRendering {
protected:
	explicit IRendering(const IRendering&) = delete;
	explicit IRendering(IRendering&&) = delete;
	IRendering& operator=(const IRendering&) = delete;
	IRendering& operator=(IRendering&&) = delete;

	IRendering() = default;
	virtual ~IRendering() = default;

public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Free() = 0;
};

#endif // !IRENDERING_H
