#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include <iostream>

using namespace glm;
using namespace std;

class Mouse
{
public:
	Mouse(void);
	~Mouse(void);
	int getButton();
	void setButton(int newButton);
	int getState();
	void setState(int newState);
	float getSensitivity();
	bool changePerspective(int x, int y);
	bool draw(int x, int y);
	void click(int button, int state);
	vec2 getPositionDelta();
	vec3 screenToWorld(int x, int y, mat4 model, mat4 projection, mat4 view);
private:
	bool firstMove;
	int button, state;
	float sensitivity;
	vec2 lastPosition;
	vec2 position;
	vec2 positionDelta;
};

