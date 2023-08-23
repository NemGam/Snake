#include "Window.h"

namespace snake {
	SDL_Window* Window::window;
	SDL_Renderer* Window::renderer;
	TTF_Font* Window::window_font;

	int Window::window_width;
	int Window::window_height; 


	Window::Window(const char* title, const int width, const int height, const char* font_path, const Uint32 flags)
	{
		window = nullptr;
		renderer = nullptr;
		window_font = nullptr;
		if (SDL_Init(SDL_INIT_VIDEO) == -1) {
			std::cerr << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
			return;
		}
		
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		if (window == nullptr) {
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr) {
			std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer could not be created!", SDL_GetError(), nullptr);
			exit(-1);
		}

		if (TTF_Init() == -1) {
			std::cerr << "TTF text was not initialized! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF text was not initialized!", SDL_GetError(), nullptr);
			exit(-1);
		}

		window_font = TTF_OpenFont(font_path, FONT_SIZE);
		if (window_font == nullptr) {
			std::cerr << "TTF failed to open! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to open the font!", SDL_GetError(), nullptr);
			exit(-1);
		}
	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

		window_height = height;
		window_width = width;
	}

	Window::~Window() {
		if (window_font != nullptr) TTF_CloseFont(window_font);
		if (renderer != nullptr) SDL_DestroyRenderer(renderer);
		if (window != nullptr) SDL_DestroyWindow(window);
		TTF_Quit();
	}

	int Window::get_height() {
		return window_height;
	}

	int Window::get_width() {
		return window_width;
	}

	SDL_Renderer* Window::get_renderer() {
		return renderer;
	}

	SDL_Window* Window::get_window() {
		return window;
	}

	TTF_Font* Window::get_font() {
		return window_font;
	}
}