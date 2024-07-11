#include "game.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <memory>

#include "logger.h"


//Arguments are used by SDL library
// ReSharper disable CppParameterNeverUsed
int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logger::LogAndShowError(SDL_GetError());
		return 1;
	}

	if (TTF_Init() != 0) {
		logger::LogAndShowError(TTF_GetError());
		return 1;
	}

	{
		const auto window = snake::Window::Create(kScreenWidth, kScreenHeight, "SNAKE", SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			SDL_Quit();
			return 1;
		}

		int code;
		do {
			snake::Game game(*window.get());
			code = game.Run();

			//Check if the game continues 
		} while (code != -1);

		
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}


