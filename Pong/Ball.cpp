#include "Ball.h"

#include <Box2D\Box2D.h>

Ball::Ball()
{
}

Ball::Ball(b2World *world)
{
	// Set the ball as a dynamic physics body in the middle of the screen
	b2BodyDef dynBodyDef;
	dynBodyDef.type = b2_dynamicBody;
	dynBodyDef.position = b2Vec2(4.0f, 3.0f);

	mBody = world->CreateBody(&dynBodyDef);
	
	b2CircleShape ballCircleShape;
	ballCircleShape.m_radius = 0.1f;
	
	b2FixtureDef ballCircleFixDef;;
	ballCircleFixDef.shape = &ballCircleShape;
	ballCircleFixDef.density = 1.0f;

	mBody->CreateFixture(&ballCircleFixDef);
	mBody->SetUserData(this);
}


Ball::~Ball()
{
}

void Ball::update()
{
	Entity::update();
}

void Ball::render(Drawer& drawer)
{
	Entity::render(drawer);
}