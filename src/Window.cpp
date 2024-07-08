#include "Window.h"
#include <string>

#include "Logger.h"

namespace snake {

	

	std::map<std::string, TTF_Font*> Window::window_fonts;

	int Window::window_width;
	int Window::window_height; 

	Window::Window(std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window, 
		std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer, int width, int height)
		: sdl_window_(std::move(sdl_window)),
		sdl_renderer_(std::move(sdl_renderer))
	{
		
	}


	std::unique_ptr<Window> Window::Create(int width, int height, const char* title, Uint32 flags) {

		logger::Log("Creating a new Window");
		if (SDL_Init(SDL_INIT_VIDEO) == -1) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}

		auto window = 
			std::unique_ptr<SDL_Window, SdlWindowDestructor>(SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags));

		if (window == nullptr) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}

		auto renderer = 
			std::unique_ptr<SDL_Renderer, SdlRendererDestructor>(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

		if (renderer == nullptr) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}

		if (TTF_Init() == -1) {
			logger::LogAndShowError(SDL_GetError());
			return nullptr;
		}

		SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
		SDL_RenderClear(renderer.get());
		SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

		window_height = height;
		window_width = width;

		return std::unique_ptr<Window>(new Window(std::move(window), std::move(renderer), width, height));
	}




	Window::~Window() {
		for (const auto& it : window_fonts) {
			TTF_CloseFont(it.second);
		}

		TTF_Quit();
	}

	int Window::GetHeight() {
		return window_height;
	}

	int Window::GetWidth() {
		return window_width;
	}

	SDL_Renderer* Window::GetRenderer() {
		return this->sdl_renderer_.get();
	}

	TTF_Font* Window::get_font(const std::string& name, int size) {
		const auto it = window_fonts.find(name + std::to_string(size));
		if (it != window_fonts.end()) {
			return it->second;
		}

		std::string key = "/";
		//Convert relative path to the absolute path
		std::string abs_font_path(RESOURCES_PATH "/resources");
		
		abs_font_path += key.append(name);

		TTF_Font* font = TTF_OpenFont(abs_font_path.c_str(), size);
		if (font == nullptr) {
			logger::LogAndShowError(TTF_GetError());
			exit(-1);
		}

		window_fonts[name + std::to_string(size)] = font;
		return font;
	}
}
