#include "Enemy.h"

#include <Box2D\Box2D.h>

namespace enemy_constants {
	const float HEIGHT = 10.0f;
	const float WIDTH = 1.0f;
}

Enemy::Enemy()
{
}

Enemy::Enemy(b2World *world)
{
	// Set the enemy rectangle on the right side of the map
	b2BodyDef kinBodyDef;
	kinBodyDef.type = b2_kinematicBody;			// The player rectangle always "wins" but CAN move, so it doesn't have to be static
	kinBodyDef.position = b2Vec2(76, 30 - enemy_constants::HEIGHT / 2);	

	mBody = world->CreateBody(&kinBodyDef);

	b2Vec2 poly[] = {
		b2Vec2(0, 0),
		b2Vec2(enemy_constants::WIDTH, 0),
		b2Vec2(enemy_constants::WIDTH, enemy_constants::HEIGHT),
		b2Vec2(0, enemy_constants::HEIGHT)
	};

	b2PolygonShape enemyPolyShape;
	enemyPolyShape.Set(poly, 4);

	b2FixtureDef enemyPolyFix;
	enemyPolyFix.shape = &enemyPolyShape;
	enemyPolyFix.friction = 0;

	mBody->CreateFixture(&enemyPolyFix);
	mBody->SetUserData(this);
}

Enemy::~Enemy()
{
}

void Enemy::moveUp()
{
	mBody->SetLinearVelocity(b2Vec2(0, -50));
}

void Enemy::moveDown()
{
	mBody->SetLinearVelocity(b2Vec2(0, 50));

}

void Enemy::stopMoving()
{
	mBody->SetLinearVelocity(b2Vec2(0, 0));

}

void Enemy::update()
{
	Entity::update();
}

void Enemy::render(Drawer& drawer)
{
	Entity::render(drawer);
}