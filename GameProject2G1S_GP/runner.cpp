#include "maze_manager.h"
#include "object_manager.h"
#include "runner.h"

runner::runner() : lastDirection{ (int)DIRECTION::UP }, sight{ 3 }, leftWeapon{ 8 } {

}

runner::~runner() {

}

void runner::update() {
	for (int yCoord = 0; yCoord < MAZE_SIDE; ++yCoord) {
		for (int xCoord = 0; xCoord < MAZE_SIDE; ++xCoord) {
			if (yCoord >= coord.y - sight && yCoord <= coord.y + sight && xCoord >= coord.x - sight && xCoord <= coord.x + sight) {
				maze_manager::get_instance()->get_current_maze()->set_cell_state(xCoord, yCoord, CELL_STATE::IN_SIGHT);
			}
			else if (maze_manager::get_instance()->get_current_maze()->get_cell_state(xCoord, yCoord) == (int)CELL_STATE::IN_SIGHT) {
				maze_manager::get_instance()->get_current_maze()->set_cell_state(xCoord, yCoord, CELL_STATE::DISCOVERED);
			}
		}
	}

	if (GetAsyncKeyState(VK_W) & 0x8000) {
		int nextCellType = maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y - 1);

		if (coord.y > 0) {
			if (nextCellType != (int)CELL_TYPE::GLADE && nextCellType != (int)CELL_TYPE::WALL) {
				coord.y--;

				Sleep(50);
			}
		}

		lastDirection = (int)DIRECTION::UP;
	}
	else if (GetAsyncKeyState(VK_S) & 0x8000) {
		int nextCellType = maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x, coord.y + 1);

		if (coord.y < MAZE_SIDE - 1) {
			if (nextCellType != (int)CELL_TYPE::GLADE && nextCellType != (int)CELL_TYPE::WALL) {
				coord.y++;

				Sleep(50);
			}
		}

		lastDirection = (int)DIRECTION::DOWN;
	}
	else if (GetAsyncKeyState(VK_A) & 0x8000) {
		int nextCellType = maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x - 1, coord.y);

		if (coord.x > 0) {
			if (nextCellType != (int)CELL_TYPE::GLADE && nextCellType != (int)CELL_TYPE::WALL) {
				coord.x--;

				Sleep(50);
			}
		}

		lastDirection = (int)DIRECTION::LEFT;
	}
	else if (GetAsyncKeyState(VK_D) & 0x8000) {
		int nextCellType = maze_manager::get_instance()->get_current_maze()->get_cell_type(coord.x + 1, coord.y);

		if (coord.x < MAZE_SIDE - 1) {
			if (nextCellType != (int)CELL_TYPE::GLADE && nextCellType != (int)CELL_TYPE::WALL) {
				coord.x++;

				Sleep(50);
			}
		}

		lastDirection = (int)DIRECTION::RIGHT;
	}
	else if (GetAsyncKeyState(VK_F) & 0x8000) {
		throw_weapon();

		Sleep(100);
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		maze_manager::get_instance()->quit();
	}
}

void runner::throw_weapon() {
	if (leftWeapon <= 0 || object_manager::get_instance()->is_weapon_thrown()) {
		return;
	}

	object_manager::get_instance()->set_thrown_weapon(true);

	leftWeapon--;
}
