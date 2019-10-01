#pragma once

#ifndef CHATTER_H
#define CHATTER_H

class Chatter final {
private:
	Chatter() = default;
	explicit Chatter(const Chatter&) = delete;
	explicit Chatter(Chatter&&) = delete;
	Chatter& operator=(const Chatter&) = delete;
	Chatter& operator=(Chatter&&) = delete;

public:
	~Chatter() = default;

public:
	static void Say() {
		std::cerr << std::endl;
	}

	template <typename T, typename... Args>
	static void Say(T val, Args... args) {
		std::cerr << val << ' ';
		Chatter::Say(args...);
	}

	template <typename T, typename... Args>
	static void Stink(T val, Args... args) {
		std::cerr << "Error: ";
		Chatter::Say(args...);
	}
};

#endif // !CHATTER_H
