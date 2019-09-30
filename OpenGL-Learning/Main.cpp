#include "stdafx.h"

#include "Application.h"

int main(int argc, char** argv) {
	try {
		Application::GetInstance()->Run();
	} catch (...) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
