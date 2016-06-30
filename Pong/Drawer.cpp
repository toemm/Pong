#include "Drawer.h"

#include "Globals.h"
#include <SDL_image.h>
#include <SDL.h>

Drawer::Drawer()
{
	// SDL 
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS, &mWindow, &mRenderer);
	SDL_SetWindowTitle(mWindow, GAME_NAME);

	// SDL_image
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);	

	if (initted != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

}


Drawer::~Drawer()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	IMG_Quit();

	// Release textures
	for (const auto& pair : mTextures) {
		SDL_DestroyTexture(pair.second);
	}

}


SDL_Texture *Drawer::loadImage(const std::string& filePath)
{
	if (mTextures.count(filePath) == 0) {
		mTextures[filePath] = 
	}

	return mTextures[filePath];
}

void Drawer::blitSurface(SDL_Texture *text, SDL_Rect *sourceRect, SDL_Rect *destRect)
{

}

void Drawer::flip()
{

}

void Drawer::clear()
{

}





void Drawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}
void Drawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}
void Drawer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{

}
void Drawer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

}
void Drawer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{

}
void Drawer::DrawString(int x, int y, const char* string, ...)
{

}
void Drawer::DrawString(const b2Vec2& p, const char* string, ...)
{

}
