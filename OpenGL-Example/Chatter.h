#pragma once

#ifndef CHATTER_H
#define CHATTER_H

namespace Chatter {

void Say();

template <typename T, typename... Args>
void Say(T val, Args... args) {
	std::cerr << val << ' ';
	Chatter::Say(args...);
}

template <typename T, typename... Args>
void Stink(T val, Args... args) {
	std::cerr << "Error: ";
	Chatter::Say(val, args...);
}

}; // namespace Chatter

#endif // !CHATTER_H
