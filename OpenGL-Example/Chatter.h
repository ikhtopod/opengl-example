#pragma once

#ifndef CHATTER_H
#define CHATTER_H

class Chatter final {
private:
	static std::stringstream s_stink;

private:
	Chatter() = default;
	explicit Chatter(const Chatter&) = delete;
	explicit Chatter(Chatter&&) = delete;
	Chatter& operator=(const Chatter&) = delete;
	Chatter& operator=(Chatter&&) = delete;

private:
	static void _Stink();

	template <typename T, typename... Args>
	static void _Stink(T val, Args... args) {
		s_stink << val << ' ';
		Chatter::_Stink(args...);
	}

public:
	~Chatter() = default;

public:
	static std::string LastStink();
	static const char* c_LastStink();

	static void Say();

public:
	template <typename T, typename... Args>
	static void Say(T val, Args... args) {
		std::cerr << val << ' ';
		Chatter::Say(args...);
	}

	template <typename T, typename... Args>
	static void Stink(T val, Args... args) {
		s_stink.str("");
		std::cerr << "Error: ";
		Chatter::_Stink(val, args...);
	}
};

#endif // !CHATTER_H
