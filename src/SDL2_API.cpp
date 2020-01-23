#include "SDL2_API.hpp"

class Texture {
public:
	Texture():w(0), h(0), tex(nullptr) {}
	Texture(Texture const &t) = default;
	
	int w, h;
	SDL_Texture* tex;
};

SDL2_API::SDL2_API()
{
	if (!sdl2Init())
	{
		std::cout << "Couldn't init sdl2 " << SDL_GetError() << std::endl;
		exit(1);
	}
}

SDL2_API::SDL2_API(SDL2_API const &)
{
}

SDL2_API::~SDL2_API()
{
	sdl2Quit();
}

void SDL2_API::sdl2Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_CloseFont(font);
	TTF_Quit();
}

bool SDL2_API::sdl2Init()
{
	Uint32	flags;
	
	for (int i = 0; i < (int)FRKey::COUNT; ++i)
	{
		GKeys[i] = false;
	}
	SDL_ShowCursor(false);
	flags = SDL_WINDOW_HIDDEN;
	if (g_fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return false;
	
	if (TTF_Init() < 0)
		return false;
	if (SDL_CreateWindowAndRenderer(0, 0, flags, &window, &renderer) < 0)
		return false;
	SDL_SetWindowTitle(window, "Pong");
	SDL_SetWindowSize(window, g_screen_width, g_screen_height);
	SDL_ShowWindow(window);
	font = TTF_OpenFont("font/game_font.TTF", 48);
	return true;
}


void SDL2_API::onMouseMove(int x, int y, int x_relative, int y_relative)
{

}

void SDL2_API::onMouseButtonClick(FRMouseButton button, bool is_released)
{

}

void SDL2_API::onKeyPressed(FRKey k)
{

}

void SDL2_API::onKeyReleased(FRKey k)
{

}

void SDL2_API::drawText(std::string const &text, int x, int y, int w, int h, SDL_Color color)
{
	Texture *texture = createTextureFromSurface(TTF_RenderText_Solid(font, text.c_str(), color));
	
	SDL_Rect r;
	r.w = w;
	r.h = h;
	r.x = x;
	r.y = y;
	
	SDL_RenderCopy(renderer, texture->tex, nullptr, &r);
	
	destroyTexture(texture);
}

Texture* SDL2_API::createTextureFromSurface(SDL_Surface *surface)
{
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	if (!texture) {
		fprintf(stderr, "Couldn't load %s\n", SDL_GetError());
		return nullptr;
	}
	Texture* s = new Texture();
	
	SDL_QueryTexture(texture, nullptr, nullptr, &s->w, &s->h);
	s->tex = texture;
	
	return s;
}

Texture* SDL2_API::createTexture(const char *path)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, path);
	if (!texture) {
		fprintf(stderr, "Couldn't load %s: %s\n", path, SDL_GetError());
		return nullptr;
	}
	
	Texture* s = new Texture();
	
	SDL_QueryTexture(texture, nullptr, nullptr, &s->w, &s->h);
	s->tex = texture;
	
	return s;
}

void SDL2_API::destroyTexture(Texture *t)
{
	if (t->tex)
	{
		SDL_DestroyTexture(t->tex);
	}
	
	delete t;
}

void SDL2_API::getTextureSize(Texture *t, int &width, int height)
{
	width = t->w;
	height = t->h;
}

void SDL2_API::drawTexture(Texture *texture, int x, int y, int w, int h)
{
	
	SDL_Rect r;
	r.w = w;
	r.h = h;
	r.x = x;
	r.y = y;
	SDL_RenderCopy(renderer, texture->tex, nullptr, &r);
}

void SDL2_API::getScreenSize(int &width, int &height)
{
	SDL_Rect viewport;
	SDL_RenderGetViewport(renderer, &viewport);
	width = viewport.w;
	height = viewport.h;
}

void SDL2_API::drawTextureWithAngle(Texture *texture, int x, int y, double angle)
{
	SDL_Rect renderQuad = {x, y, texture->w, texture->h};
	SDL_RenderCopyEx(renderer, texture->tex, nullptr, &renderQuad, angle, nullptr, SDL_FLIP_NONE);
}

SDL_Window *SDL2_API::getWin() const
{
	return window;
}

SDL_Renderer *SDL2_API::getRenderer() const
{
	return renderer;
}

int SDL2_API::getFps() const
{
	return fps;
}

void SDL2_API::setFps(int fps)
{
	SDL2_API::fps = fps;
}
