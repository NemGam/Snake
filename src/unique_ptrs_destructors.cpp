#include <SDL2/SDL_render.h>
#include "unique_ptrs_destructors.h"
#include "logger.h"

namespace snake {

	void SdlWindowDestructor::operator()(SDL_Window* w) const {
		SDL_DestroyWindow(w);
	}

	void SdlRendererDestructor::operator()(SDL_Renderer* r) const {
		SDL_DestroyRenderer(r);
	}

	void SdlSurfaceDestructor::operator()(SDL_Surface* s) const {
		SDL_FreeSurface(s);
	}

	void SdlTextureDestructor::operator()(SDL_Texture* t) const {
		SDL_DestroyTexture(t);
	}

	void TtfFontDestructor::operator()(TTF_Font* f) const {
		TTF_CloseFont(f);
	}

}
