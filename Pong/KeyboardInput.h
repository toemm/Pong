#pragma once

#include <SDL.h>

#include <map>

class KeyboardInput
{
public:
	KeyboardInput() = default;
	~KeyboardInput() = default;

	SDL_Event event;

	void beginNewFrame();
	void keyUpEvent();
	void keyDownEvent();

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;



};

