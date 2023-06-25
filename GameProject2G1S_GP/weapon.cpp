#include "maze_manager.h"
#include "object_manager.h"
#include "griever.h"
#include "runner.h"
#include "weapon.h"

weapon::weapon() : direction{ object_manager::get_instance()->get_runner()->get_last_direction() } {
	coord = { object_manager::get_instance()->get_runner()->get_x_coord(), object_manager::get_instance()->get_runner()->get_y_coord() };
}

weapon::~weapon() {

}

void weapon::update() {
	switch (direction) {
	case (int)DIRECTION::UP: {
		coord.y--;
	}

						   break;

	case (int)DIRECTION::DOWN: {
		coord.y++;
	}

							 break;

	case (int)DIRECTION::LEFT: {
		coord.x--;
	}

							 break;

	case (int)DIRECTION::RIGHT: {
		coord.x++;
	}
	}

	Sleep(100);
}
