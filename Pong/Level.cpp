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

	boundary.position = b2Vec2(40, 59);
	mBot = World->CreateBody(&boundary);
	boundary.position = b2Vec2(40, 1);
	mTop = World->CreateBody(&boundary);

	b2EdgeShape edge;
	edge.Set(b2Vec2(-40, 0.0f), b2Vec2(40, 0.0f));

	b2FixtureDef edgeFixDef;
	edgeFixDef.shape = &edge;
	edgeFixDef.friction = 0;

	mBot->CreateFixture(&edgeFixDef);
	mTop->CreateFixture(&edgeFixDef);

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