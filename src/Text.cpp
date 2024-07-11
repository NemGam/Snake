#include "text.h"

#include "logger.h"
#include "window.h"
#include "unique_ptrs_destructors.h"

namespace snake {

	Text::Text(const Window& window, TTF_Font* font, int x_pos, int y_pos, const std::string& text, std::unique_ptr<SDL_Texture, SdlTextureDestructor> text_texture, 
	           TextAlignment alignment, SDL_Color color)
		: x_pos_(x_pos), y_pos_(y_pos), text_(text), window_(window), rect_{ 0, 0, 0, 0 },
		font_(font), text_texture_(std::move(text_texture)), color_(color), alignment_(alignment)
	{
		
		logger::Log("Created Text");
		TTF_SizeUTF8(font_, text_.c_str(), &rect_.w, &rect_.h);
		rect_ = GetAlignedRect(rect_, alignment);
	}

	std::unique_ptr<Text> Text::Create(const Window& window, TTF_Font* font, int x_pos, int y_pos, const std::string& text,
	                                   TextAlignment alignment, SDL_Color color) {
		//Create a surface
		auto surface = std::unique_ptr<SDL_Surface, SdlSurfaceDestructor>(TTF_RenderUTF8_Solid(font, text.c_str(), color));
		if (!surface) {
			logger::LogAndShowError(TTF_GetError());
			return nullptr;
		}

		logger::Log(std::to_string(surface->clip_rect.h) + " " + std::to_string(surface->clip_rect.w));

		//Create a texture from the created surface
		auto text_texture = 
			std::unique_ptr<SDL_Texture, SdlTextureDestructor>(
				SDL_CreateTextureFromSurface((window.GetRenderer()), surface.get()));

		if (!text_texture) {
			logger::LogAndShowError(TTF_GetError());
			return nullptr;
		}

		return std::unique_ptr<Text>(new Text(window, font, x_pos, y_pos, text, std::move(text_texture), alignment, color));
	}

	void Text::SetText(const std::string& text) {
		text_ = text;
		Regenerate();
	}

	void Text::Regenerate() {
		auto surface = std::unique_ptr<SDL_Surface, SdlSurfaceDestructor>(TTF_RenderUTF8_Solid(font_, text_.c_str(), color_));
		if (!surface) {
			logger::LogAndShowError(TTF_GetError());
			return;
		}

		//Destroy the old texture and create a new one
		text_texture_.reset(SDL_CreateTextureFromSurface((window_.GetRenderer()), surface.get()));

		if (!text_texture_) {
			logger::LogAndShowError(TTF_GetError());
			return;
		}

		TTF_SizeUTF8(font_, text_.c_str(), &rect_.w, &rect_.h);
		rect_ = GetAlignedRect(rect_, alignment_);
	}

	SDL_Rect Text::GetAlignedRect(SDL_Rect rect, TextAlignment alignment) {

		rect.y = y_pos_;

		switch (alignment) {
			case TextAlignment::kLeft:
				rect.x = x_pos_;
				break;
			case TextAlignment::kMiddle:
				rect.x = x_pos_ - rect.w / 2;
				break;
			case TextAlignment::kRight:
				rect.x = x_pos_ - rect.w;
				break;
		}

		return rect;
	}

	void Text::Render() const {

		if (SDL_RenderCopy((window_.GetRenderer()), text_texture_.get(), nullptr, &rect_) != 0) {
			logger::Log(SDL_GetError());
		}
	}
}
