#pragma once
#include <random>
#include <vector>
#include "define.h"

class maze {
	std::vector<std::vector<std::pair<int, int>>> mazeData;
	std::random_device rd;

public:
	maze();

	~maze();

	int get_cell_type(int xCoord, int yCoord) {
		return mazeData[yCoord][xCoord].first;
	}

	int get_cell_state(int xCoord, int yCoord) {
		return mazeData[yCoord][xCoord].second;
	}

	void render_maze();

	void render_maze_once();

	void render_black();

	void generate_maze(int, int);

	void set_cell_type(int xCoord, int yCoord, CELL_TYPE cellType) {
		mazeData[yCoord][xCoord].first = (int)cellType;
	}

	void set_cell_state(int xCoord, int yCoord, CELL_STATE cellState) {
		mazeData[yCoord][xCoord].second = (int)cellState;
	}
};

