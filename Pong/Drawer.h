#pragma once

#include <Box2D\Box2D.h>
#include <SDL.h>

#include <string>
#include <map>

class Drawer
{
public:
	Drawer();
	~Drawer();

	// General purpose rendering for Pong (via OpenGL)
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
	void DrawString(int x, int y, const char* string, ...);
	void DrawString(const b2Vec2& p, const char* string, ...);

	// Multiply vertices of Fixtures->Shapes with the current body's transformation matrix
	void DrawShape(b2Transform& transf, b2Fixture *fix, b2Color& col);

	// like SDL_RenderClear (clear the back buffer)
	void Clear();

	// like SDL_RenderPresent (swap the front with the back buffer);
	void Swap();


private:
	SDL_Window *mWindow;
	SDL_GLContext mGLContext;

	// Prepare a Projection Matrix for drawing with a 2D View with Eyes on (0,0), like SDL coordinate system
	void prepareCoordinateSystem() const;

	// Reset the projection matrix to restore state before drawing
	void resetCoordinateSystem() const;


	// Initialize libraries
	bool init();

	// Clear ressources
	void cleanup();

	// Check and print SDL errors if there are any
	void checkSDLError(int line = -1);

	// Set OpenGL attributes
	void setOpenGLAttributes();

	// Print various set SDL_GL_Attributes like version number
	void printSDL_GL_Attributes();
};

