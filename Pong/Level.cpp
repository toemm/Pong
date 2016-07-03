#include "Level.h"
#include "Drawer.h"
#include "Globals.h"

#include <SDL.h>
#include <Box2D\Box2D.h>


Level::Level()
{
	// Create the physics world
	World = new b2World(b2Vec2(0, 0));	// Zero gravity

	// Draw top and bottom boundaries
	b2BodyDef boundary;
	boundary.type = b2_staticBody;

	boundary.position = b2Vec2(4.0f, 5.9f);
	mBot = World->CreateBody(&boundary);
	boundary.position = b2Vec2(4.0f, 0.1f);
	mTop = World->CreateBody(&boundary);

	b2EdgeShape edge;

	edge.Set(b2Vec2(-4.0f, 0.0f), b2Vec2(4.0f, 0.0f));
	mBot->CreateFixture(&edge, 0.0f);
	mTop->CreateFixture(&edge, 0.0f);

}

Level::~Level()
{
	delete World;
}




void Level::render(Drawer& drawer)
{
	b2Transform trans = mTop->GetTransform();
	drawer.DrawShape(trans, mTop->GetFixtureList(), b2Color(1, 1, 1));

	trans = mBot->GetTransform();
	drawer.DrawShape(trans, mTop->GetFixtureList(), b2Color(1, 1, 1));
}


void Level::update()
{
	// Update the world, calculate interaction between b2Bodies
	World->Step(SCREEN_TICKS_PER_FRAME, 8, 3);
}