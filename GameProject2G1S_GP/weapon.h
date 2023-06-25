#pragma once
#include "object.h"

class weapon : public object {
	int direction;

public:
	weapon();

	~weapon();

	int get_direction() {
		return direction;
	}

	void update();
};

