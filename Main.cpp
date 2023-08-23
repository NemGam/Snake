#include "Game.h"
#include "Window.h"


//Arguments are used by SDL library
// ReSharper disable CppParameterNeverUsed
int main(int argc, char* args[])
{
	auto window = snake::Window("SNAKE", screen_width, screen_height, SDL_WINDOW_SHOWN);
	int code;
	do {
		auto* game = new snake::Game(&window);
		code = game->run();
		delete game;
		//Check if the game continues 
	} while (code != -1);
	SDL_Quit();
    return 0;
}
