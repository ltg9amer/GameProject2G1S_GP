#pragma once
#include "object.h"

class runner : public object {
	int lastDirection, sight, leftWeapon;

public:
	runner();

	~runner();

	int get_last_direction() {
		return lastDirection;
	}

	int get_left_weapon() {
		return leftWeapon;
	}

	void update();

	void set_last_direction(int direction) {
		lastDirection = direction;
	}

	void throw_weapon();
};

