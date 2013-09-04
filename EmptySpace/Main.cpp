#include "Game.h"

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/GL.h>
#include <glut.h>

int main(int argc, char* argv[])
{

	Game g = Game();

	try
	{
		g.run();
	}
	catch(int exception)
	{
		std::cout << "Exception caought: " << exception << std::endl;
	}

	return 0;
}