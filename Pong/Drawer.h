#pragma once

#include <Box2D\Box2D.h>

#include <string>
#include <map>

struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;

class Drawer
{
public:
	Drawer();
	~Drawer();

	// For the background image or other simple texturing
	SDL_Texture *loadImage(const std::string& filePath);
	void blitSurface(SDL_Texture *text, SDL_Rect *sourceRect, SDL_Rect *destRect);
	void flip();
	void clear();

	// General purpose rendering for Pong (via OpenGL)
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
	void DrawString(int x, int y, const char* string, ...);
	void DrawString(const b2Vec2& p, const char* string, ...);

private:
	SDL_Renderer *mRenderer;
	SDL_Window *mWindow;

	std::map<std::string, SDL_Texture *> mTextures;

};

