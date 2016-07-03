#include "Player.h"

#include <Box2D\Box2D.h>

Player::Player()
{
}

Player::Player(b2World *world)
{
	// Set the player rectangle on the left side of the map
	b2BodyDef kinBodyDef;
	kinBodyDef.type = b2_dynamicBody;			// The player rectangle always "wins" but CAN move, so it doesn't have to be static
	kinBodyDef.position = b2Vec2(0.3f, 3.0f);

	mBody = world->CreateBody(&kinBodyDef);

	b2Vec2 poly[] = {
		b2Vec2(0, 0),
		b2Vec2(0.1, 0),
		b2Vec2(0.1, 0.3),
		b2Vec2(0, 0.3)
	};

	b2PolygonShape playerPolyShape;
	playerPolyShape.Set(poly, 4);

	b2FixtureDef playerPolyFix;
	playerPolyFix.shape = &playerPolyShape;
	//playerPolyFix.density = 1.0f;
	//playerPolyFix.friction = 1.0f;

	mBody->CreateFixture(&playerPolyFix);
	mBody->SetUserData(this);
	//mBody->SetGravityScale(0);
}

void Player::moveUp()
{
	mBody->SetLinearVelocity(b2Vec2(0, -0.01));

}

void Player::moveDown()
{
	mBody->SetLinearVelocity(b2Vec2(0, 0.01));
}

void Player::stopMoving()
{
	mBody->SetLinearVelocity(b2Vec2(0, 0));
}

Player::~Player()
{
}

void Player::update() 
{
	Entity::update();
}

void Player::render(Drawer& drawer)
{
	Entity::render(drawer);
}