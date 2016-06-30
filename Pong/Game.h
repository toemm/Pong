#pragma once

#include "Drawer.h"
#include "KeyboardInput.h"



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

	bool mRunning;
	Drawer mDrawer;
	KeyboardInput mInput;
};

