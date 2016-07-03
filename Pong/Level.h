#pragma once

struct SDL_Texture;
class Drawer;
class b2World;
class b2Body;

class Level
{
public:
	Level();
	~Level();


	void render(Drawer& drawer);
	void update();

	b2World *World;

private:
	
	b2Body *mTop;
	b2Body *mBot;

};

