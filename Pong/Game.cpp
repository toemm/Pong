#include "Game.h"
#include "Drawer.h"
#include <SDL.h>



Game::Game()
{
	Init();
}


Game::~Game()
{

}

void Game::Init()
{
	mRunning = true;
	mLevel = Level(mDrawer);
	GameLoop();
}

void Game::GameLoop()
{
	while (mRunning) {
		Input();
		Update();
		Render();
	}
}

void Game::Input()
{
	mInput.beginNewFrame();
	if (SDL_PollEvent(&mInput.event)) {

		switch (mInput.event.type) {
		case SDL_KEYDOWN:
			if (mInput.event.key.repeat == 0) {
				mInput.keyDownEvent();
			}
			break;
		case SDL_KEYUP:
			mInput.keyUpEvent();
			break;
		default:
			break;
		}
	}

	// Process Input
	if (mInput.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
		mRunning = false;
	}


}

void Game::Update()
{
	mLevel.update();
}

void Game::Render()
{
	mLevel.render(mDrawer);
}