#pragma once

#include "Globals.h"

#include "Controller.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <glut.h>
#include <assert.h>

enum EXCEPTIONS{
	GAME_COULD_NOT_INIT_SDL,
	GAME_COULD_NOT_CREATE_WINDOW,
	GAME_COULD_NOT_CREATE_RENDERER,
	GAME_COULD_NOT_CREATE_GL_CONTEXT
};

enum GAME_STATE{
	GAME_RUNNING,
	GAME_CLEANING,
	GAME_LOADING,
	GAME_PAUSED
};

class Game
{
public:
	Game(void);
	~Game(void);

	void init();
	void init_gl();
	void render();
	void update();
	void handleEvents();
	void clean();
	void run();

public:
	GAME_STATE gamestate;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
	SDL_GLContext glContext;

	int windowWidth;
	int windowHeight;

private:
	float mouseSpeed;
	float startTime;
	float frameStart;
	float frameTime;
	float fps;
	float framesPerSecond;
	float totalFrames;
	float delayTime;

	Controller* controller;

	SDL_Event event;

};

