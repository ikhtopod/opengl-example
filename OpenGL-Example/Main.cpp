#include "stdafx.h"

#include "Application.h"

int main() {
	try {
		Application app {};
		app.Run();
	} catch (const std::exception&) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
