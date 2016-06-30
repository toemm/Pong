#include "KeyboardInput.h"


// Called at the beginning of each new frame to 
// reset the keys that are no longer relevant
void KeyboardInput::beginNewFrame()
{
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

// Called when key is released
void KeyboardInput::keyUpEvent()
{
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;

}

// This gets called when a key is pressed
void KeyboardInput::keyDownEvent()
{
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}

bool KeyboardInput::wasKeyPressed(SDL_Scancode key)
{
	return this->_pressedKeys[key];
}

bool KeyboardInput::wasKeyReleased(SDL_Scancode key)
{
	return this->_releasedKeys[key];
}

bool KeyboardInput::isKeyHeld(SDL_Scancode key)
{
	return this->_heldKeys[key];
}