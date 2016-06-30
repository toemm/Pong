#include "Level.h"
#include "Drawer.h"

#include <SDL.h>


Level::Level(Drawer& drawer)
{
	mBackground = drawer.loadImage("content/background/grass.png");
}

Level::~Level()
{
	// Free the background texture
	SDL_DestroyTexture(mBackground);
}




void Level::render(Drawer& drawer)
{
	// Render the background image
	drawer.blitSurface(mBackground, NULL, NULL);
}

void Level::update()
{

}