#pragma once

#include "Entity.h"

class b2World;
class Drawer;

class Ball :
	public Entity
{
public:
	Ball();
	Ball(b2World *world);
	~Ball();

	void update() override;
	void render(Drawer& drawer) override;

};

