#pragma once
#include "Components.h"
class TransformComponenet :public Component {
private:
	int xpos;
	int ypos;
public:
	TransformComponenet()
	{
		xpos = 0;
		ypos = 0;
	}
	TransformComponenet(int x, int y) {
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