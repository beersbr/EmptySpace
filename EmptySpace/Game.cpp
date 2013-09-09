#include "Game.h"

Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw GAME_COULD_NOT_INIT_SDL;

	//windowWidth = 1280;
	//windowHeight = 800;

	windowWidth = 1920;
	windowHeight = 1080;

	pWindow = SDL_CreateWindow("Emtpy Space v0.01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(!pWindow)
		throw GAME_COULD_NOT_CREATE_WINDOW;

	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	if(!pRenderer)
		throw GAME_COULD_NOT_CREATE_RENDERER;

	glContext = SDL_GL_CreateContext(pWindow);

	if(!glContext)
		throw GAME_COULD_NOT_CREATE_GL_CONTEXT;

	frameStart = 0.0f;
	frameTime = 0.0f;
	fps = 60.0f;
	framesPerSecond = 0.0f;
	totalFrames = 0;

	delayTime = 1000.0/fps;

	gamestate = GAME_RUNNING;
}

void Game::init_gl()
{
	SDL_GL_SetSwapInterval(1);
	glewInit();

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	gluOrtho2D(-100, 100, -100, 100);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHTING);

	//glEnable(GL_MULTISAMPLE_ARB);
	//glEnable(GL_MULTISAMPLE);
	
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat ratio = (GLfloat)windowWidth/(GLfloat)windowHeight;
	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(50.0f, ratio, 0.1f, 1500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void Game::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float fTriangle[9] = {
		-0.4f, 0.1f, 0.0f,
		0.4f, 0.1f, 0.0f,
		0.0f, 0.7f, 0.0
	};

	float fQuad[12] = {
		-0.2f, -0.1f, 0.0f,
		-0.2f, -0.6f, 0.0f,
		0.2f, -0.1f, 0.0f,
		0.2f, -0.6, 0.0f
	};

	UINT uiVBO[2];

	glGenBuffers(2, uiVBO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), fTriangle, GL_STATIC_DRAW);

	// We just clear color
	glClear(GL_COLOR_BUFFER_BIT); 

	glEnableVertexAttribArray(0); 
	// Triangle render
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glDrawArrays(GL_TRIANGLES, 0, 3); 

	SDL_GL_SwapWindow(pWindow);
}

void Game::update()
{
	if(Controller::instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		gamestate = GAME_CLEANING;
}

void Game::handleEvents()
{
	Controller::instance()->resetMouseMoved();
	Controller::instance()->resetKeyPressed();
	Controller::instance()->resetMouseClicks();

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
			{
				gamestate = GAME_CLEANING;
				break;
			}
			case SDL_KEYDOWN:
			{
				Controller::instance()->onKeyDown(event.key.keysym.scancode);
				break;
			}
			case SDL_KEYUP:
			{
				Controller::instance()->onKeyUp(event.key.keysym.scancode);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				Controller::instance()->onMouseMove(event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				Controller::instance()->onMouseDown(event.button.button, event.button.x, event.button.y);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				Controller::instance()->onMouseUp(event.button.button, event.button.x, event.button.y);
				break;
			}
			case SDL_WINDOWEVENT:
			{
				switch(event.window.event)
				{
				case SDL_WINDOWEVENT_HIDDEN:
					Controller::instance()->showMouse();
					break;
				case SDL_WINDOWEVENT_SHOWN:
					Controller::instance()->hideMouse();
					break;
				case SDL_WINDOWEVENT_LEAVE:
					Controller::instance()->showMouse();
					break;
				case SDL_WINDOWEVENT_ENTER:
					Controller::instance()->hideMouse();
					break;
				}
				break;
			}
		}
	}
}

void Game::clean()
{

}

void Game::run()
{
	init();
	init_gl();

	startTime = SDL_GetTicks();

	while(gamestate == GAME_RUNNING)
	{
		frameStart = SDL_GetTicks();

		handleEvents();
		update();
		render();
		
		++totalFrames;
		framesPerSecond = totalFrames/((float)SDL_GetTicks() - startTime)/1000.0;

		std::cerr << framesPerSecond << std::endl;

		frameTime = SDL_GetTicks() - frameStart;
		if(frameTime < delayTime)
			SDL_Delay((int)(delayTime - frameTime));
	}

	clean();
}
