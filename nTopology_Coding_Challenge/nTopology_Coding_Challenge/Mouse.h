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
	bool move(int x, int y);
	void click(int button, int state);
	vec2 getPositionDelta();
private:
	int button, state;
	float sensitivity;
	vec2 lastPosition;
	vec2 position;
	vec2 positionDelta;
};

