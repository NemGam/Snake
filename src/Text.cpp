#include "Text.h"
#include "Window.h"
namespace snake {
	Text::Text(Window* window, TTF_Font* font, int xpos, int ypos, const std::string& text, const text_alignment alignment, SDL_Color color)
		: rect{ 0, 0, 0, 0 }, font(font), text_texture(nullptr), color(color), alignment(alignment)
	{
		this->window = window;
		//Create a surface
		SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
		if (!surface) {
			std::cerr << "Failed to create a text: " << TTF_GetError() << std::endl;
			return;
		}
		//Set text rect to the created surface rect
		this->rect = surface->clip_rect;

		//Create a texture from the created surface
		this->text_texture = SDL_CreateTextureFromSurface(window->GetRenderer(), surface);
		if (!this->text_texture){
			std::cerr << "Failed to create a texture: " << TTF_GetError() << std::endl;
			return;
		}

		//Move the text according to desired alignment
		switch (alignment) {
		case left:
			this->rect = { xpos - rect.w / 2 - rect.w, ypos - rect.h / 2, rect.w, rect.h };
			break;
		case middle:
			this->rect = { xpos - rect.w / 2, ypos - rect.h / 2, rect.w, rect.h };
			break;
		case right:
			this->rect = { xpos - rect.w / 2 + rect.w, ypos - rect.h / 2, rect.w, rect.h };
			break;
		}

		//Get rid of the surface
		SDL_FreeSurface(surface);
	}

	Text::~Text() {
		SDL_DestroyTexture(this->text_texture);
	}

	/**
	 * \brief Set the text of the Text object.
	 * \param text the text to set
	 */
	void Text::set_text(const std::string& text) {
		recreate(text);
	}

	void Text::recreate(const std::string& text) {
		SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
		if (!surface) {
			std::cerr << "Failed to create a surface: " << TTF_GetError() << std::endl;
			SDL_FreeSurface(surface);	
			return;
		}

		SDL_DestroyTexture(text_texture);
		text_texture = SDL_CreateTextureFromSurface(window->GetRenderer(), surface);
		if (!text_texture) {
			std::cerr << "Failed to create a texture: " << TTF_GetError() << std::endl;
			return;
		}
		const int prev_w = rect.w;
		TTF_SizeUTF8(font, text.c_str(), &rect.w, &rect.h);
		switch (alignment) {
		case left:
			rect = { rect.x, rect.y, rect.w, rect.h };
			break;
		case middle: 
			rect = { (rect.x + (prev_w - rect.w) / 2), rect.y, rect.w, rect.h };
			break;
		case right: 
			rect = { (rect.x + (prev_w - rect.w)), rect.y, rect.w, rect.h };
			break;
		}
		SDL_FreeSurface(surface);
	}

	void Text::render() const {
		SDL_RenderCopy(window->GetRenderer(), text_texture, nullptr, &rect);
	}
}
