#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <memory>


namespace snake {

	struct SdlWindowDestructor {
		void operator()(SDL_Window* w) const {
			SDL_DestroyWindow(w);
		}
	};

	struct SdlRendererDestructor {
		void operator()(SDL_Renderer* r) const {
			SDL_DestroyRenderer(r);
		}
	};


	constexpr int kFontSize = 200;
	class Window
	{
	public:

		static std::unique_ptr<Window> Create(int width, int height, const char* title, Uint32 flags);


		~Window();

		SDL_Renderer* GetRenderer();

		int GetHeight();

		int GetWidth();

		//Get the font used within the window.
		static TTF_Font* get_font(const std::string& name, int size);

	private:
		Window(std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window,
			std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer, int width, int height);
		
		std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window_;
		std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer_;
		static std::map<std::string, TTF_Font*> window_fonts;
		static int window_height;
		static int window_width;
	};
}
#endif