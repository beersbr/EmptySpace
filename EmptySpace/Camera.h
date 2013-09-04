#pragma once

#include "Vector.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <glut.h>

class Camera
{
public:
	Camera(void);

	void update();

public:
	Vector pos;
	Vector direction;
	Vector target;
};

