#include "Logger.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace logger {
	void Log(const std::string& message) {
		std::cout << message << "\n";
	}

	void LogError(const std::string& message) {
		std::cerr << "ERROR: " << message << "\n";
	}

	void LogAndShowError(const std::string& message, SDL_Window* window) {
		LogError(message);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", message.c_str(), window);
	}

}




