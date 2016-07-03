#pragma once


class b2Body;
class Drawer;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update();
	virtual void render(Drawer& drawer);

	const inline int getCurrentHP() const { return this->mCurrentHP; }

	const inline float getX() const { return mX; }
	const inline float getY() const { return mX; }

	const inline void setX(float x) { mX = x; }
	const inline void setY(float y) { mY = y; }

protected:
	int mCurrentHP;
	b2Body *mBody;

private:
	float mX, mY;


};

