#pragma once
#include "define.h"

class object {
protected:
	POINT coord;

public:
	void set_coord(int xCoord, int yCoord) {
		coord = { xCoord, yCoord };
	}

	int get_x_coord() {
		return coord.x;
	}

	int get_y_coord() {
		return coord.y;
	}
};

