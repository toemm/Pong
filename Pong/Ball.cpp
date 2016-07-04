#include "Ball.h"

#include <Box2D\Box2D.h>

#include <time.h>
#include <cstdlib>

Ball::Ball()
{
}

Ball::Ball(b2World *world)
{
	// Set the ball as a dynamic physics body in the middle of the screen
	b2BodyDef dynBodyDef;
	dynBodyDef.type = b2_dynamicBody;
	dynBodyDef.position = b2Vec2(40, 30);
	dynBodyDef.bullet = true;

	mBody = world->CreateBody(&dynBodyDef);
	
	b2CircleShape ballCircleShape;
	ballCircleShape.m_radius = 0.5;
	
	b2FixtureDef ballCircleFixDef;;
	ballCircleFixDef.shape = &ballCircleShape;
	ballCircleFixDef.density = 20;
	ballCircleFixDef.restitution = 1;

	mBody->CreateFixture(&ballCircleFixDef);
	mBody->SetUserData(this);

	kickoff();
}

void Ball::reset()
{
	mBody->SetTransform(b2Vec2(40, 30), mBody->GetAngle());
	kickoff();
}

void Ball::kickoff()
{

	srand(time(NULL));
	if (rand() % 2) {
		mBody->SetLinearVelocity(b2Vec2(25, 25));
	}
	else {
		mBody->SetLinearVelocity(b2Vec2(-25, -25));
	}
}


Ball::~Ball()
{
}

void Ball::update()
{
	if (getX() < 0 || getX() > 80) {
		reset();
	}

	Entity::update();
}

void Ball::render(Drawer& drawer)
{
	Entity::render(drawer);
}