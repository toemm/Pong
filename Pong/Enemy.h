#pragma once

#include "Entity.h"

class b2World;
class Drawer;

class Enemy :
	public Entity
{
public:
	Enemy();
	Enemy(b2World *world);
	~Enemy();

	void moveUp();
	void moveDown();
	void stopMoving();

	void update() override;
	void render(Drawer& drawer) override;

};

