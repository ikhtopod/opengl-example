#pragma once

#ifndef TRIADA_H
#define TRIADA_H

class Triada {
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Free() = 0;
};

#endif // !TRIADA_H
