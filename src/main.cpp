#include "Game.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <memory>


//Arguments are used by SDL library
// ReSharper disable CppParameterNeverUsed
int main(int argc, char* argv[])
{
	auto window = snake::Window::Create(screen_width, screen_height, "SNAKE", SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		return 0;
	}

	int code;
	do {
		auto game = snake::Game(window.get());
		code = game.run();

		//Check if the game continues 
	} while (code != -1);

	SDL_Quit();
	return 0;
}


