#include "Mouse.h"

Mouse::Mouse(void)
{
	firstMove = true;
	sensitivity = 0.05f;
	lastPosition =  vec2(800.0f / 2.0f, 600.0f / 2.0f);
}

Mouse::~Mouse(void)
{
}

int Mouse::getButton()
{
	return button;
}

void Mouse::setButton(int newButton)
{
	button = newButton;
}

int Mouse::getState()
{
	return state;
}

void Mouse::setState(int newState)
{
	state = newState;
}

float Mouse::getSensitivity()
{
	return sensitivity;
}

vec2 Mouse::getPositionDelta()
{
	return positionDelta;
}

bool Mouse::move(int x, int y)
{
	if (state == GLUT_DOWN 
		&& button == GLUT_LEFT_BUTTON
		&& glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		position = vec2(x,y);

		if (firstMove)
		{
			lastPosition = position;
			firstMove = false;
		}
		
		positionDelta = vec2(position.x - lastPosition.x, lastPosition.y - position.y);
		lastPosition = position;
		return true;
	}
	return false;
}

void Mouse::click(int button, int state)
{
	setButton(button);
	setState(state);
}
