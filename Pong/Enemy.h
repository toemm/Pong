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

	void update() override;
	void render(Drawer& drawer) override;

};

