#pragma once
#include "maze.h"

class maze;

class maze_manager {
	static maze_manager* instance;
	POINT startCoord;
	maze* mazes[MAZE_PATTERN_AMOUNT];
	std::random_device rd;
	clock_t startTime, leftTime;
	int mazeIndex, changeTime;

	maze_manager();

	~maze_manager();

public:
	static maze_manager* get_instance() {
		if (instance == nullptr) {
			instance = new maze_manager;
		}

		return instance;
	}

	static void destroy_instance() {
		if (instance) {
			delete instance;

			instance = nullptr;
		}
	}

	maze* get_current_maze() {
		return mazes[mazeIndex];
	}


	void init();

	void update();

	void quit();

	void fail();

	void clear();

	bool render_timer();

	bool check_blade_coord(int);
};

