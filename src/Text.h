#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "window.h"

namespace snake {

	//TODO: FIX SEG FAULT. GETTING DOUBLE DELETE OF FONT PROBABLY WHICH IS OWNED BY WINDOW

	class Text {
	public:
		enum class TextAlignment { kLeft = 0, kMiddle = 1, kRight = 2 };


		static std::unique_ptr<Text> Create(const Window& window, TTF_Font* font, int x_pos, int y_pos, 
			const std::string& text = "New Text", TextAlignment alignment = TextAlignment::kLeft, 
			SDL_Color color = { 255, 255, 255, 255 });


		Text(const Text&) = delete;
		Text(Text&& t) = delete;
		Text& operator=(const Text&) = delete;
		Text&& operator=(Text&& t) = delete;
		

		~Text() = default;


		void SetText(const std::string& text);
		void Render() const;


	private:
		Text(const Window& window, TTF_Font* font, int x_pos, int y_pos, const std::string& text,
			std::unique_ptr<SDL_Texture, SdlTextureDestructor> text_texture, TextAlignment alignment, SDL_Color color);


		void Regenerate();
		SDL_Rect GetAlignedRect(SDL_Rect rect, TextAlignment alignment); //Modifies provided rect to be of a given alignment

		int x_pos_;
		int y_pos_;
		std::string text_;
		const Window& window_;
		SDL_Rect rect_;
		TTF_Font* font_;
		std::unique_ptr<SDL_Texture, SdlTextureDestructor> text_texture_;
		SDL_Color color_;
		TextAlignment alignment_;
	};
}
#endif
