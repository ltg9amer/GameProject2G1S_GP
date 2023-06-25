#include <iostream>
#include "audio_manager.h"
#include "console.h"
#include "maze_manager.h"
#include "object_manager.h"
#include "griever.h"
#include "runner.h"

maze_manager* maze_manager::instance = nullptr;

maze_manager::maze_manager() : startCoord{ MAZE_SIDE / 2, MAZE_SIDE - 2 }, startTime{ clock() }, leftTime{ clock() }, mazeIndex{ 0 }, changeTime{ 20 } {
	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		mazes[i] = nullptr;
	}
}

maze_manager::~maze_manager() {

}

void maze_manager::init() {
	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		mazes[i] = new maze;

		mazes[i]->generate_maze(MAZE_SIDE / 2, MAZE_SIDE - 2);
		mazes[i]->set_cell_type(MAZE_SIDE / 2, MAZE_SIDE - 1, CELL_TYPE::GLADE);
	}

	while (true) {
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> xCoordDis(0, MAZE_SIDE - 1);

		int bladeXCoord = xCoordDis(gen);

		if (check_blade_coord(bladeXCoord)) {
			for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
				mazes[i]->set_cell_type(bladeXCoord, 0, CELL_TYPE::BLADE);
			}

			break;
		}
	}
}

void maze_manager::update() {
	griever* grievers[MAZE_PATTERN_AMOUNT];

	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		grievers[i] = object_manager::get_instance()->get_griever(i);
	}

	runner* player = object_manager::get_instance()->get_runner();
	weapon* thrownWeapon = nullptr;

	if (mazes[mazeIndex]->get_cell_type(startCoord.x, startCoord.y) == (int)CELL_TYPE::WALL) {
		if (mazes[mazeIndex]->get_cell_type(startCoord.x + 1, startCoord.y + 1) != (int)CELL_TYPE::WALL) {
			player->set_coord(startCoord.x + 1, startCoord.y + 1);
		}
		else if (mazes[mazeIndex]->get_cell_type(startCoord.x - 1, startCoord.y + 1) != (int)CELL_TYPE::WALL) {
			player->set_coord(startCoord.x - 1, startCoord.y + 1);
		}
		else if (mazes[mazeIndex]->get_cell_type(startCoord.x + 1, startCoord.y - 1) != (int)CELL_TYPE::WALL) {
			player->set_coord(startCoord.x + 1, startCoord.y - 1);
		}
		else {
			player->set_coord(startCoord.x - 1, startCoord.y - 1);
		}
	}
	else {
		player->set_coord(startCoord.x, startCoord.y);
	}

	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, MAZE_SIDE - 2);

	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		if (!grievers[i]->is_dead()) {
			while (true) {
				int xCoord = dis(gen);
				int yCoord = dis(gen);

				if (mazes[mazeIndex]->get_cell_type(xCoord, yCoord) == (int)CELL_TYPE::ROAD) {
					grievers[i]->set_coord(xCoord, yCoord);

					break;
				}
			}
		}
	}

	go_to_xy(0, 0);
	object_manager::get_instance()->update();
	mazes[mazeIndex]->render_black();
	mazes[mazeIndex]->render_maze_once();

	startTime = clock();

	while (!render_timer()) {
		go_to_xy(0, 0);
		object_manager::get_instance()->update();
		mazes[mazeIndex]->render_maze();

		if (object_manager::get_instance()->is_weapon_thrown()) {
			thrownWeapon = object_manager::get_instance()->get_thrown_weapon();

			thrownWeapon->update();

			for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
				if (!grievers[i]->is_dead()) {
					if (thrownWeapon->get_x_coord() == grievers[i]->get_x_coord() && thrownWeapon->get_y_coord() == grievers[i]->get_y_coord()) {
						grievers[i]->kill();

						delete thrownWeapon;

						object_manager::get_instance()->set_thrown_weapon(false);
					}
				}
			}

			if (object_manager::get_instance()->is_weapon_thrown()) {
				if (mazes[mazeIndex]->get_cell_type(thrownWeapon->get_x_coord(), thrownWeapon->get_y_coord()) != (int)CELL_TYPE::ROAD)
				{
					delete thrownWeapon;

					object_manager::get_instance()->set_thrown_weapon(false);
				}
			}
		}

		if (mazes[mazeIndex]->get_cell_type(player->get_x_coord(), player->get_y_coord()) == (int)CELL_TYPE::BLADE) {
			clear();
		}

		for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
			if (!grievers[i]->is_dead()) {
				if (player->get_x_coord() == grievers[i]->get_x_coord() && player->get_y_coord() == grievers[i]->get_y_coord()) {
					Sleep(1000);
					fail();
				}
			}
		}
	}

	if (object_manager::get_instance()->is_weapon_thrown()) {
		delete thrownWeapon;

		object_manager::get_instance()->set_thrown_weapon(false);
	}

	startCoord = { player->get_x_coord(), player->get_y_coord() };
	(++mazeIndex) %= MAZE_PATTERN_AMOUNT;
}

void maze_manager::quit() {
	mazes[mazeIndex]->render_black();
	audio_manager::get_instance()->stop_bgm();
	set_color((int)COLOR::RED, (int)COLOR::BLACK);

	std::string giveUpText = "YOU GAVE UP...";
	int x = 18, y = 9;

	for (char word : giveUpText) {
		go_to_xy(x++, y);

		std::cout << word;

		Sleep(200);
	}

	Sleep(1000);
	mazes[mazeIndex]->render_black();
	set_color((int)COLOR::WHITE, (int)COLOR::BLACK);
	system("cls");
	destroy_instance();
	object_manager::destroy_instance();
	exit(1);
}

void maze_manager::fail() {
	mazes[mazeIndex]->render_black();
	audio_manager::get_instance()->stop_bgm();
	set_color((int)COLOR::RED, (int)COLOR::BLACK);

	std::string failText = "YOU FAILED...";
	int x = 18, y = 9;

	for (char word : failText) {
		go_to_xy(x++, y);

		std::cout << word;

		Sleep(200);
	}

	Sleep(1000);
	mazes[mazeIndex]->render_black();
	audio_manager::get_instance()->stop_bgm();
	set_color((int)COLOR::WHITE, (int)COLOR::BLACK);
	system("cls");
	destroy_instance();
	object_manager::destroy_instance();
	exit(1);
}

void maze_manager::clear() {
	mazes[mazeIndex]->render_black();
	audio_manager::get_instance()->stop_bgm();
	set_color((int)COLOR::LIGHT_BLUE, (int)COLOR::WHITE);
	system("cls");

	std::string clearText = "YOU ESCAPED!";
	int x = 19, y = 9;

	for (char word : clearText) {
		go_to_xy(x++, y);

		std::cout << word;

		Sleep(200);
	}

	Sleep(1000);
	mazes[mazeIndex]->render_black();
	set_color((int)COLOR::WHITE, (int)COLOR::BLACK);
	system("cls");
	destroy_instance();
	object_manager::destroy_instance();
	exit(1);
}

bool maze_manager::render_timer() {
	leftTime = changeTime - (clock() - startTime) / CLOCKS_PER_SEC;

	set_color((int)COLOR::WHITE, (int)COLOR::BLACK);

	if (leftTime >= 10) {
		go_to_xy(43, 2);

		std::cout << leftTime << "초";
	}
	else {
		go_to_xy(43, 2);

		std::cout << ' ' << leftTime << "초";
	}

	int renderY = 4;

	for (int i = 0; i < (changeTime - leftTime) / 2; ++i) {
		go_to_xy(43, renderY++);
		set_color((int)COLOR::LIGHT_GRAY, (int)COLOR::BLACK);

		std::cout << "■■";
	}

	for (int i = 0; i < leftTime / 2; ++i) {
		go_to_xy(43, renderY++);
		set_color((int)COLOR::LIGHT_VIOLET, (int)COLOR::BLACK);

		std::cout << "■■";
	}

	go_to_xy(43, 16);
	set_color((int)COLOR::RED, (int)COLOR::BLACK);

	std::cout << "무기";

	go_to_xy(44, 17);

	std::cout << object_manager::get_instance()->get_runner()->get_left_weapon() << "개";

	if (leftTime <= 0) {
		return true;
	}

	return false;
}

bool maze_manager::check_blade_coord(int bladeXCoord) {
	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		if (mazes[i]->get_cell_type(bladeXCoord, 1) != (int)CELL_TYPE::ROAD) {
			return false;
		}
	}

	return true;
}
