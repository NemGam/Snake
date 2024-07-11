#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <memory>
#include "unique_ptrs_destructors.h"

namespace snake {

	constexpr int kFontSize = 200;
	class Window
	{
	public:
		static std::unique_ptr<Window> Create(int width, int height, const char* title, Uint32 flags);


		SDL_Renderer* GetRenderer() const;
		int GetHeight() const;
		int GetWidth() const;
		TTF_Font* GetFont(const std::string& name, int size) const;


		~Window();
	private:
		Window(std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window,
			std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer, int width, int height);




		std::unique_ptr<SDL_Window, SdlWindowDestructor> sdl_window_;
		std::unique_ptr<SDL_Renderer, SdlRendererDestructor> sdl_renderer_;
		mutable std::map<std::string, std::unique_ptr<TTF_Font, TtfFontDestructor>> window_fonts_;
		int window_height_;
		int window_width_;



	};
}
#endif