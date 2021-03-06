#pragma once

#include "Drawer.h"
#include "KeyboardInput.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"



class Game
{
public:
	Game();
	~Game();

private:
	// Initialize libraries and engines
	void Init();

	// Main GameLoop
	void GameLoop();

	// The Holy 3
	void Input();
	void Update();
	void Render();

	// Helpers
	void registerInput();
	void processInput();

	bool mRunning;
	Drawer mDrawer;
	KeyboardInput mInput;

	Level mLevel;
	Ball mBall;
	Player mPlayer;
	Enemy mEnemy;

};

