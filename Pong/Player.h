#pragma once

#include "Entity.h"

class b2World;
class Drawer;

class Player :
	public Entity
{
public:
	Player(b2World *world);
	Player();
	~Player();

	void moveUp();
	void moveDown();
	void stopMoving();

	void update() override;
	void render(Drawer& drawer) override;

};

