#pragma once
#include "main.hpp"

enum class FRKey
{
	RIGHT,
	LEFT,
	DOWN,
	UP,
	RESET,
	COUNT
};

enum class FRMouseButton
{
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

static int g_screen_width = 1024;
static int g_screen_height = 768;
static bool g_fullscreen = false;

extern bool GKeys[(int)FRKey::COUNT];

class Texture;

class SDL2_API
{
public:
protected:
	
	SDL2_API();
	
	SDL2_API(SDL2_API const &);
	
	~SDL2_API();

public:
	bool			sdl2Init();
	Texture*		createTexture(const char *path);
	Texture*		createTextureFromSurface(SDL_Surface *surface);
	void			destroyTexture(Texture *t);
	void			drawText(std::string const &text, int x, int y, int w, int h, SDL_Color color);
	void			getTextureSize(Texture *t, int &width, int height);
	void			drawTexture(Texture *texture, int x, int y, int w, int h);
	void			drawTextureWithAngle(Texture *texture, int x, int y, double angle);
	void			getScreenSize(int &width, int &height);
	void			onMouseMove(int x, int y, int x_relative, int y_relative);
	void			onMouseButtonClick(FRMouseButton button, bool is_released);
	void			onKeyPressed(FRKey k);
	void			onKeyReleased(FRKey k);
	void			sdl2Quit();

public:
	int				getFps() const;
	
	void			setFps(int fps);
	
	SDL_Window		*getWin() const;
	
	SDL_Renderer	*getRenderer() const;

protected:
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	TTF_Font		*font;
	int 			old_time;
	int				fps = 1;
	int 			last_mouse_x;
	int 			last_mouse_y;
};


