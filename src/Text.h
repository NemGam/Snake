#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "Window.h"

namespace snake {

	class Text {
	public:
		enum text_alignment { left = 0, middle = 1, right = 2 };

		Text(Window* window, TTF_Font* font, int xpos, int ypos, const std::string& = " ", text_alignment alignment = left, SDL_Color color = {255, 255, 255, 255});

		~Text();

		/**
		 * @brief Set the text of this text object.
		 * @param text text to set.
		*/
		void set_text(const std::string& text);

		void render() const;

	private:
		Window* window;

		SDL_Rect rect;
		TTF_Font* font;
		SDL_Texture* text_texture;
		SDL_Color color;
		text_alignment alignment;

		void recreate(const std::string& text);
	};
}
#endif
