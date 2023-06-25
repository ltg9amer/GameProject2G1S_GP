#include <iostream>
#include "audio_manager.h"
#include "console.h"
#include "maze_manager.h"
#include "object_manager.h"
#include "start.h"

void init();

int main() {
	init();

	while (true) {
		maze_manager::get_instance()->update();
	}
}

void init() {
	system("mode con cols=50 lines=20 | title Maze Runner: The Square");
	set_color((int)COLOR::RED, (int)COLOR::BLACK);
	cursor_set(false, 1);

	while (true) {
		system("cls");
		render_title();

		int menu = render_menu();

		if (!menu) {
			break;
		}
		else if (menu == 1) {
			render_info();
		}
		else {
			maze_manager::get_instance()->quit();
		}
	}

	maze_manager::get_instance()->init();
	object_manager::get_instance()->init();
	audio_manager::get_instance()->init();
}