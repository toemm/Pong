#include "Enemy.h"

#include <Box2D\Box2D.h>

Enemy::Enemy()
{
}

Enemy::Enemy(b2World *world)
{
	// Set the enemy rectangle on the right side of the map
	b2BodyDef kinBodyDef;
	kinBodyDef.type = b2_kinematicBody;			// The player rectangle always "wins" but CAN move, so it doesn't have to be static
	kinBodyDef.position = b2Vec2(7.6f, 3.0f);

	mBody = world->CreateBody(&kinBodyDef);

	b2Vec2 poly[] = {
		b2Vec2(0, 0),
		b2Vec2(0.1, 0),
		b2Vec2(0.1, 0.3),
		b2Vec2(0, 0.3)
	};

	b2PolygonShape enemyPolyShape;
	enemyPolyShape.Set(poly, 4);

	b2FixtureDef enemyPolyFix;
	enemyPolyFix.shape = &enemyPolyShape;
	enemyPolyFix.density = 1.0f;
	enemyPolyFix.friction = 1.0f;

	mBody->CreateFixture(&enemyPolyFix);
	mBody->SetUserData(this);
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	Entity::update();
}

void Enemy::render(Drawer& drawer)
{
	Entity::render(drawer);
}