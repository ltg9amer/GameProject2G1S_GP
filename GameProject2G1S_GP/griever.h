#pragma once
#include <ctime>
#include <random>
#include "object.h"

class griever : public object {
	std::random_device rd;
	clock_t startTime;
	bool isDead;
	int direction;
	double moveDelay;

public:
	griever();

	~griever();

	bool is_dead() {
		return isDead;
	}

	void update();

	void kill() {
		isDead = true;
	}
};

