#pragma once
#include <string>
#include <SDL2/SDL.h>

namespace logger {
	//Logs given message. Does not flush the buffer.
	void Log(const std::string& message);

	//Logs given error message. Does not flush the buffer.
	void LogError(const std::string& message);

	void LogAndShowError(const std::string& message, SDL_Window* window = nullptr);
}


