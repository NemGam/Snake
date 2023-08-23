#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace snake {
	constexpr int FONT_SIZE = 200;
	class Window
	{
	public:
		/**
		 * @brief Creates a new window.
		 * @param title The title of the window.
		 * @param width The width of the window.
		 * @param height The height of the window.
		 * @param font_path Path to the font to use to render text.
		 * @param flags Flags to set to the window.
		*/
		Window(const char* title, int width, int height, const char* font_path, Uint32 flags);

		~Window();

		/**
		 * @brief Get main window.
		 * @return Main window.
		*/
		static SDL_Window* get_window();
		
		/**
		 * @brief Get main renderer.
		 * @return Main renderer.
		*/
		static SDL_Renderer* get_renderer();

		/**
		 * @brief Get the height of the window.
		 * @return Height of the window.
		*/
		static int get_height();

		/**
		 * @brief Get the width of the window.
		 * @return Width of the window.
		*/
		static int get_width();

		/**
		 * @brief Get font used within the window.
		 * @return Font used within the window
		*/
		static TTF_Font* get_font();

	private:
		static SDL_Window* window;
		static SDL_Renderer* renderer;
		static TTF_Font* window_font;
		static int window_height;
		static int window_width;
	};
}
#endif