#include "Entity.h"
#include "Drawer.h"

#include <Box2D\Box2D.h>

Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::update()
{
	b2Vec2 currentPosition = mBody->GetPosition();
	mX = currentPosition.x;
	mY = currentPosition.y;
}

void Entity::render(Drawer& drawer)
{
	// Iterate through the fixtures of a body if it has more than 1
	for (auto fixture = mBody->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
		// Get the objects current transformation matrix
		// transf.p = translation vector (i.e. body.getPosition)
		// transf.q = rotation vector (sin, cos)
		b2Transform transf = mBody->GetTransform();
		drawer.DrawShape(transf, fixture, b2Color(1, 1, 1));
	}
}