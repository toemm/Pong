#include "Drawer.h"
#include "Globals.h"
#include <SDL_image.h>

#include <GL\glew.h>

#include <iostream>
#include <math.h>
#include <array>

Drawer::Drawer()
{
	if (!init()) {
		std::cout << "Error initializing, shutting down.\n";
		cleanup();
	}
	else {
		printSDL_GL_Attributes();
		std::cout << "Initiation successful. Game is starting...\n";
	}
}

bool Drawer::init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to init SDL\n";
		return false;
	}

	// Create a Window that is usable with OpenGL context
	mWindow = SDL_CreateWindow(
		GAME_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS
		);

	if (!mWindow) {
		std::cout << "Unable to create window\n";
		checkSDLError(__LINE__);
		return false;
	}

	// Connect the rendering context to the SDL Window
	mGLContext = SDL_GL_CreateContext(mWindow);

	setOpenGLAttributes();

	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::cout << "Warning: Unable to set VSync!" << std::endl;
		checkSDLError();
	}

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	return true;
}

void Drawer::setOpenGLAttributes()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}




void Drawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

	prepareCoordinateSystem();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < vertexCount; i++) {
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();

	glPopMatrix();	// GL_MODELVIEW

	resetCoordinateSystem();

}
void Drawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	prepareCoordinateSystem();

	// In order to make the inside of the polygons translucent, colors are blended together
	glEnable(GL_BLEND);

	// BlenFunc describes the blending process
	// 1. The source primitive's colors are modified by the alpha value  -> scaling factor for scaling of the source color
	// 2. The destination color's are modified by (1-<value from 1.>)	-> scaling factor for scaling the dest color
	// 3. The two values from 1. and 2. are added together and drawn
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// 1. source alpha 0.25, dest alpha 1-0.25 = 0.75
	// DestColor = 0.25 * colA + 0.75 * colB  (Color b is more visible after blending together the two colors)
	glColor4f(color.r, color.g, color.b, 0.25f);

	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i < vertexCount; i++) {
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();

	// Draw a 1.0f polygon around to mark the edges
	// source alpha = 1.0f, dest alpha = 0.0f
	glColor4f(color.r, color.g, color.b, 1.0f);

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < vertexCount; i++) {
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();

	glDisable(GL_BLEND);
	glPopMatrix(); // GL_MODELVIEW

	resetCoordinateSystem();
}
void Drawer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	prepareCoordinateSystem();

	float segments = 20.0f;
	float segment_degrees_rad = 2.0 * M_PI / segments;
	float theta = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {
		b2Vec2 coords = center + (radius * b2Vec2(cosf(theta), sinf(theta)));
		glVertex2f(coords.x, coords.y);
		theta += segment_degrees_rad;

	}
	glEnd();
	glPopMatrix(); // GL_MODELVIEW

	resetCoordinateSystem();
}
void Drawer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	prepareCoordinateSystem();

	float segments = 20.0f;
	float segment_degrees_rad = 2.0 * M_PI / segments;	// every 15 degrees or so
	float theta = 0.0f;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Filled triangles
	glColor4f(color.r, color.g, color.b, 0.25f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < segments; i++) {
		b2Vec2 coords = center + (radius * b2Vec2(cosf(theta), sinf(theta)));
		glVertex2f(coords.x, coords.y);
		theta += segment_degrees_rad;
	}
	glEnd();

	// Frame around circle
	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);

	for (int i = theta = 0; i < segments; i++) {
		b2Vec2 coords = center + (radius * b2Vec2(cosf(theta), sinf(theta)));
		glVertex2f(coords.x, coords.y);
		theta += segment_degrees_rad;
	}
	glEnd();

	glDisable(GL_BLEND);
	glPopMatrix(); // GL_MODELVIEW

	resetCoordinateSystem();
}
void Drawer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	prepareCoordinateSystem();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(color.r, color.g, color.b);
	glPointSize(size);

	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();


	resetCoordinateSystem();
}

void Drawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	prepareCoordinateSystem();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();

	glPopMatrix();

	resetCoordinateSystem();
}

void Drawer::DrawShape(b2Transform& transf, b2Fixture *fix, b2Color& col)
{
	// The shape contains the vertices/points of the primitive structure
	// The coordinates of the vertices are in local coordinates and need to be transformed
	// Transformation is done via translation and rotation with the b2Transform of the body the shape is living in
	b2Shape *shape = fix->GetShape();

	switch (shape->GetType()) {

	case b2Shape::e_polygon:
		{
			b2PolygonShape *pShape = dynamic_cast<b2PolygonShape *>(shape);
			int vertexCount = pShape->GetVertexCount();
	
			b2Vec2 poly[b2_maxPolygonVertices];

			for (int i = 0; i < vertexCount; i++) {
				poly[i] = b2Mul(transf, pShape->m_vertices[i]);

			}
			DrawSolidPolygon(poly, vertexCount, col);
		}
		break;

	case b2Shape::e_circle:
		{
			b2CircleShape *cShape = dynamic_cast<b2CircleShape *>(shape);
			b2Vec2 cent = b2Mul(transf, cShape->m_p);
			DrawSolidCircle(cent, cShape->m_radius, col);
		}
		break;

	case b2Shape::e_edge:
		{
			b2EdgeShape *eShape = dynamic_cast<b2EdgeShape *>(shape);
			b2Vec2 p1 = b2Mul(transf, eShape->m_vertex1);
			b2Vec2 p2 = b2Mul(transf, eShape->m_vertex2);
			DrawSegment(p1, p2, col);
		}
		break;

	default:
		break;
	}
}

void Drawer::DrawString(int x, int y, const char* string, ...)
{

}
void Drawer::DrawString(const b2Vec2& p, const char* string, ...)
{

}

void Drawer::prepareCoordinateSystem() const
{
	// Prepare the Projection matrix stack
	glMatrixMode(GL_PROJECTION);

	// Push the current Projection matrix on the stack (most likely it's the identity matrix already)
	glPushMatrix();

	// Load a fresh identity matrix
	glLoadIdentity();

	// Multiple identity matrix with Orthogonal matrix
	// This sets a new 2D coordinate system that's roughly equal to the SDL coordinate system with eyes on (0,0)

	// Run the game in MKS (meters, kilograms, seconds) because Box2D works with these units
	// ONLY scale to pixels via the constant PTM (pixels to meter) when the pixels are needed for drawing purposes
	glOrtho(0, SCREEN_WIDTH / PTM, SCREEN_HEIGHT / PTM, 0, -1, 1);
}


void Drawer::resetCoordinateSystem() const
{
	// Switch onto the projection matrix stack
	glMatrixMode(GL_PROJECTION);

	// Pop the current matrix (most likely orthogonal matrix) 
	glPopMatrix();

	// Reset state by having the default matrix
	glMatrixMode(GL_MODELVIEW);

}



void Drawer::Clear()
{
	// Clear the color buffer to the value set in glClearColor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Drawer::Swap()
{
	SDL_GL_SwapWindow(mWindow);
}



void Drawer::cleanup()
{
	SDL_DestroyWindow(mWindow);
	SDL_GL_DeleteContext(mGLContext);
	SDL_Quit();
}

void Drawer::checkSDLError(int line)
{
	std::string error = SDL_GetError();

	if (error != "") {
		std::cout << "SDL Error : " << error << std::endl;
		if (line != -1) {
			std::cout << "\nLine : " << line << std::endl;
		}
		SDL_ClearError();
	}
}

void Drawer::printSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION: " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}


Drawer::~Drawer()
{
	cleanup();
}