#pragma once

#include <map>

#include <SDL.h>

struct MouseClick
{
	int button;
	int x;
	int y;
};

class Controller
{
public:
	static Controller* instance();
	
	void onKeyDown(short keyCode);
	void onKeyUp(short keyCode);
	void onMouseMove(int offX, int offY, int mX, int mY);
	void onMouseDown(int button, int x, int y);
	void onMouseUp(int button, int x, int y);

	bool isKeyDown(short keyCode);
	bool isKeyPressed(short keyCode);

	bool isMouseButtonDown(short button);
	bool isMouseButtonPressed(short button);

	void resetKeyPressed();

	int offsetX();
	int offsetY();
	int mouseX();
	int mouseY();

	void showMouse();
	void hideMouse();

	void resetMouseClicks();
	void resetMouseMoved();
	bool mouseMoved();

	void setMouseSpeed(float ms);
	float getMouseSpeed();

private:
	Controller(void);

	bool mouseDidMove;

	int offsetx, offsety;
	int mousex, mousey;
	float mouseSpeed;

	std::map<short, bool> keyStatus;
	std::map<short, bool> keyPressed;

	std::map<short, bool> mouseStatus;
	std::map<short, bool> mousePressed;

	static Controller* _instance;
};