#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "Triada.h"

class Input final : public Triada {
public: // Triada
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Free() override;
};

#endif // !INPUT_H
