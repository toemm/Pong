#pragma once

struct SDL_Texture;
class Drawer;

class Level
{
public:
	Level() = default;
	Level(Drawer& drawer);
	~Level();


	void render(Drawer& drawer);
	void update();



private:
	SDL_Texture *mBackground;
};

