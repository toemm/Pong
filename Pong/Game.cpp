#include "Game.h"
#include "Drawer.h"
#include "Player.h"
#include "Ball.h"
#include "Enemy.h"

#include <SDL.h>
#include <GL\glew.h>
#include <Box2D\Box2D.h>

Game::Game()
{
	Init();
	GameLoop();
}


Game::~Game()
{

}

void Game::Init()
{
	mRunning = true;
	mPlayer = Player(mLevel.World);
	mBall = Ball(mLevel.World);
	mEnemy = Enemy(mLevel.World);
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
	registerInput();
	processInput();
}

void Game::registerInput()
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
}

void Game::processInput()
{
	if (mInput.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
		mRunning = false;
	}

	if (mInput.isKeyHeld(SDL_SCANCODE_W)) {
		mPlayer.moveUp();
	}

	if (mInput.isKeyHeld(SDL_SCANCODE_S)) {
		mPlayer.moveDown();
	}

	if (!mInput.isKeyHeld(SDL_SCANCODE_W) && !mInput.isKeyHeld(SDL_SCANCODE_S)) {
		mPlayer.stopMoving();
	}
}

void Game::Update()
{
	mLevel.update();
	mPlayer.update();
	mBall.update();
	mEnemy.update();
}

void Game::Render()
{
	mDrawer.Clear();

	mLevel.render(mDrawer);
	mPlayer.render(mDrawer);
	mBall.render(mDrawer);
	mEnemy.render(mDrawer);

	mDrawer.Swap();
}