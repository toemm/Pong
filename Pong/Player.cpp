#include "Player.h"

#include <Box2D\Box2D.h>

namespace player_constants {
	const float HEIGHT = 10.0f;
	const float WIDTH = 1.0f;
}

Player::Player()
{
}

Player::Player(b2World *world)
{
	// Set the player rectangle on the left side of the map
	b2BodyDef kinBodyDef;
	kinBodyDef.type = b2_kinematicBody;			// The player rectangle always "wins" but CAN move, so it doesn't have to be static
	kinBodyDef.position = b2Vec2(3, 30 - player_constants::HEIGHT / 2);	

	mBody = world->CreateBody(&kinBodyDef);

	b2Vec2 poly[] = {
		b2Vec2(0, 0),
		b2Vec2(player_constants::WIDTH, 0),
		b2Vec2(player_constants::WIDTH, player_constants::HEIGHT),
		b2Vec2(0, player_constants::HEIGHT)
	};

	b2PolygonShape playerPolyShape;
	playerPolyShape.Set(poly, 4);

	b2FixtureDef playerPolyFix;
	playerPolyFix.shape = &playerPolyShape;
	playerPolyFix.friction = 0;

	mBody->CreateFixture(&playerPolyFix);
	mBody->SetUserData(this);
}

void Player::moveUp()
{
	mBody->SetLinearVelocity(b2Vec2(0, -50));

}

void Player::moveDown()
{
	mBody->SetLinearVelocity(b2Vec2(0, 50));
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