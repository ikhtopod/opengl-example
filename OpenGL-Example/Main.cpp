#include "stdafx.h"

#include "Application.h"

int main() {
	try {
		Application app {};
		app.Run();
	} catch (const std::exception & ex) {
		Chatter::Stink(ex.what());
		return EXIT_FAILURE;
	} catch (...) {
		Chatter::Stink("Unknown exception");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
