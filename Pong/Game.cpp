#include "Game.h"
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
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	mRunning = true;

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

}

void Game::Update()
{

}

void Game::Render()
{

}