#pragma once
#include "Components.h"
class PositionComponenet :public Component {
private:
	int xpos;
	int ypos;
public:
	PositionComponenet()
	{
		xpos = 0;
		ypos = 0;
	}
	PositionComponenet(int x, int y) {
		xpos = x;
		ypos = y;
	}
	void update()override {
		xpos++;
		ypos++;
	}
	int x() { return xpos; }
	void x(int x) { xpos = x; }
	int y() { return ypos; }
	void y(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }
};