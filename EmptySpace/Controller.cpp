#include "Controller.h"


Controller* Controller::_instance = nullptr;

Controller* Controller::instance()
{
	if(Controller::_instance == nullptr)
		Controller::_instance = new Controller();

	return Controller::_instance;
}

Controller::Controller(void)
{
	keyStatus.clear();
	mouseDidMove = false;
	mouseSpeed = 0.015f;
}

void Controller::onKeyDown(short keyCode)
{
	keyStatus[keyCode] = true;
}

void Controller::onKeyUp(short keyCode)
{
	keyStatus[keyCode] = false;
	keyPressed[keyCode] = true;
}

void Controller::onMouseMove(int offx, int offy, int mX, int mY)
{
	mouseDidMove = true;
	offsetx = offx;
	offsety = offy;
	mousex = mX;
	mousey = mY;
}

void Controller::onMouseDown(int button, int x, int y)
{
	mouseStatus[button] = true;
}

void Controller::onMouseUp(int button, int x, int y)
{
	mouseStatus[button] = false;
	mousePressed[button] = true;
}

bool Controller::isMouseButtonDown(short button)
{
	return mouseStatus[button];
}

bool Controller::isMouseButtonPressed(short button)
{
	return mousePressed[button];
}

void Controller::resetMouseClicks()
{
	mousePressed.clear();
}

bool Controller::isKeyDown(short keyCode)
{
	return keyStatus[keyCode];
}

bool Controller::isKeyPressed(short keyCode)
{
	return keyPressed[keyCode];
}

void Controller::resetKeyPressed()
{
	keyPressed.clear();
}

int Controller::offsetX()
{
	return offsetx;
}

int Controller::offsetY()
{
	return offsety;
}

int Controller::mouseX()
{
	return mousex;
}

int Controller::mouseY()
{
	return mousey;
}

void Controller::showMouse()
{
	SDL_SetRelativeMouseMode((SDL_bool)false);
}


void Controller::hideMouse()
{
	SDL_SetRelativeMouseMode((SDL_bool)true);
}

void Controller::resetMouseMoved()
{
	mouseDidMove = false;
}

bool Controller::mouseMoved()
{
	return mouseDidMove;
}

void Controller::setMouseSpeed(float ms)
{
	mouseSpeed = ms;
}

float Controller::getMouseSpeed()
{
	return mouseSpeed;
}