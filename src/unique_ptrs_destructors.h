#ifndef UNIQUE_PTRS_DESTRUCTORS_H
#define UNIQUE_PTRS_DESTRUCTORS_H
#include <SDL2/SDL_ttf.h>

namespace snake {
	struct SdlWindowDestructor {
		void operator()(SDL_Window* w) const;
	};

	struct SdlRendererDestructor {
		void operator()(SDL_Renderer* r) const;
	};

	struct SdlSurfaceDestructor {
		void operator()(SDL_Surface* s) const;
	};

	struct SdlTextureDestructor {
		void operator()(SDL_Texture* t) const;
	};

	struct TtfFontDestructor {
		void operator()(TTF_Font* f) const;
	};
}
#endif // UNIQUE_PTRS_DESTRUCTORS_H
