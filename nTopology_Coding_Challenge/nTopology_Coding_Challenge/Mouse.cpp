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

bool Mouse::changePerspective(int x, int y)
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
		
		positionDelta = position - lastPosition;//vec2(position.x - lastPosition.x, lastPosition.y - position.y);
		lastPosition = position;
		return true;
	}
	return false;
}

bool Mouse::draw(int x, int y)
{
	if (state == GLUT_DOWN 
		&& button == GLUT_LEFT_BUTTON)
	{
		return true;
	}
	return false;
}

void Mouse::click(int button, int state)
{
	setButton(button);
	setState(state);
}

/*vec3 Mouse::screenToWorld(int x, int y, int width, int height, mat4 model, mat4 projection, mat4 view)
{
	double u = 2.0 * winX / width - 1;
    double v = - 2.0 * winY / height + 1;
    mat4 viewProjectionInverse = inverse(projection * view);

    vec4 world(u,v,1.0f,1.0f); 
	cout << u << ", " << v << ", " << 1.0f << endl;
    return vec3(viewProjectionInverse * world);
}*/
