#include "stdafx.h"
#include "Chatter.h"

std::stringstream Chatter::s_stink {};

void Chatter::_Stink() {
	std::cerr << s_stink.str() << std::endl;
}

std::string Chatter::LastStink() {
	return s_stink.str();
}

const char* Chatter::c_LastStink() {
	return s_stink.str().c_str();
}

void Chatter::Say() {
	std::cerr << std::endl;
}
