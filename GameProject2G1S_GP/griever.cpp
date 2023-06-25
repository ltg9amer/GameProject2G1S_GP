#include "griever.h"
#include "maze_manager.h"

griever::griever() : isDead{ false }, startTime{ clock() }, direction{ (int)DIRECTION::DOWN }, moveDelay{ 0.75 } {

}

griever::~griever() {

}

void griever::update() {
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 3);

	if ((clock() - startTime) / CLOCKS_PER_SEC >= moveDelay) {
		switch (direction) {
		case (int)DIRECTION::UP: {
			if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y - 1) == (int)CELL_TYPE::ROAD) {
				coord.y--;
				startTime = clock();
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x - 1, coord.y) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::LEFT;
					}
				}

					  break;

				case 2: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x + 1, coord.y) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::RIGHT;
					}
				}

					  break;

				default:

					break;
				}
			}
			else {
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					direction = (int)DIRECTION::DOWN;
				}

					  break;

				case 2: {
					direction = (int)DIRECTION::LEFT;
				}

					  break;

				case 3: {
					direction = (int)DIRECTION::RIGHT;
				}

					  break;
				}
			}
		}

							   break;

		case (int)DIRECTION::DOWN: {
			if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y + 1) == (int)CELL_TYPE::ROAD) {
				coord.y++;
				startTime = clock();
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x - 1, coord.y) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::LEFT;
					}
				}

					  break;

				case 2: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x + 1, coord.y) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::RIGHT;
					}
				}

					  break;

				default:

					break;
				}
			}
			else {
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					direction = (int)DIRECTION::UP;
				}

					  break;

				case 2: {
					direction = (int)DIRECTION::LEFT;
				}

					  break;

				case 3: {
					direction = (int)DIRECTION::RIGHT;
				}

					  break;
				}
			}
		}

								 break;

		case (int)DIRECTION::LEFT: {
			if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x - 1, coord.y) == (int)CELL_TYPE::ROAD) {
				coord.x--;
				startTime = clock();
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y - 1) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::UP;
					}
				}

					  break;

				case 2: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y + 1) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::DOWN;
					}
				}

					  break;

				default:

					break;
				}
			}
			else {
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					direction = (int)DIRECTION::UP;
				}

					  break;

				case 2: {
					direction = (int)DIRECTION::DOWN;
				}

					  break;

				case 3: {
					direction = (int)DIRECTION::RIGHT;
				}

					  break;
				}
			}
		}

								 break;

		case (int)DIRECTION::RIGHT: {
			if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x + 1, coord.y) == (int)CELL_TYPE::ROAD) {
				coord.x++;
				startTime = clock();
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y - 1) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::UP;
					}
				}

					  break;

				case 2: {
					if (maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y + 1) == (int)CELL_TYPE::ROAD) {
						direction = (int)DIRECTION::DOWN;
					}
				}

					  break;

				default:

					break;
				}
			}
			else {
				int selector = dis(gen);

				switch (selector) {
				case 1: {
					direction = (int)DIRECTION::UP;
				}

					  break;

				case 2: {
					direction = (int)DIRECTION::DOWN;
				}

					  break;

				case 3: {
					direction = (int)DIRECTION::LEFT;
				}

					  break;
				}
			}
		}

								  break;
		}
	}
}
