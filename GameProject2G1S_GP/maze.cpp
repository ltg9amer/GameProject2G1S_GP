#include <iostream>
#include "console.h"
#include "griever.h"
#include "maze.h"
#include "object_manager.h"
#include "runner.h"

maze::maze() : mazeData{ std::vector<std::vector<std::pair<int, int>>>(MAZE_SIDE, std::vector<std::pair<int, int>>(MAZE_SIDE, {(int)CELL_TYPE::WALL, (int)CELL_STATE::UNDISCOVERED})) } {

}

maze::~maze() {

}

void maze::render_maze() {
	bool isGrieverRendered = false;
	int playerXCoord, playerYCoord, startXCoord, endXCoord, startYCoord, endYCoord, renderY = 0;
	playerXCoord = object_manager::get_instance()->get_runner()->get_x_coord();
	playerYCoord = object_manager::get_instance()->get_runner()->get_y_coord();
	startXCoord = std::clamp(playerXCoord - (RENDER_SIDE / 2 - 1), 0, MAZE_SIDE - RENDER_SIDE);
	endXCoord = std::clamp(playerXCoord + RENDER_SIDE / 2, RENDER_SIDE - 1, MAZE_SIDE - 1);
	startYCoord = std::clamp(playerYCoord - (RENDER_SIDE / 2 - 1), 0, MAZE_SIDE - RENDER_SIDE);
	endYCoord = std::clamp(playerYCoord + RENDER_SIDE / 2, RENDER_SIDE - 1, MAZE_SIDE - 1);

	for (int yCoord = startYCoord; yCoord <= endYCoord; ++yCoord) {
		go_to_xy(0, renderY++);

		for (int xCoord = startXCoord; xCoord <= endXCoord; ++xCoord) {
			switch (mazeData[yCoord][xCoord].first) {
			case (int)CELL_TYPE::GLADE: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::UNDISCOVERED) {
					set_color((int)COLOR::BLACK, (int)COLOR::BLACK);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::RED, (int)COLOR::GRAY);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::LIGHT_RED, (int)COLOR::YELLOW);
				}

				std::cout << "■";
			}

									  break;

			case (int)CELL_TYPE::ROAD: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::UNDISCOVERED) {
					set_color((int)COLOR::BLACK, (int)COLOR::BLACK);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::LIGHT_GRAY, (int)COLOR::LIGHT_GRAY);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::BLACK, (int)COLOR::LIGHT_YELLOW);

					for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
						if (!object_manager::get_instance()->get_griever(i)->is_dead()) {
							if (xCoord == object_manager::get_instance()->get_griever(i)->get_x_coord() && yCoord == object_manager::get_instance()->get_griever(i)->get_y_coord()) {
								std::cout << "※";

								isGrieverRendered = true;

								break;
							}
						}
					}
				}

				if (isGrieverRendered) {
					isGrieverRendered = false;
				}
				else {
					if (xCoord == playerXCoord && yCoord == playerYCoord) {
						int direction = object_manager::get_instance()->get_runner()->get_last_direction();

						switch (direction) {
						case (int)DIRECTION::UP: {
							std::cout << "▲";
						}

											   break;

						case (int)DIRECTION::DOWN: {
							std::cout << "▼";
						}

												 break;

						case (int)DIRECTION::LEFT: {
							std::cout << "◀";
						}

												 break;

						case (int)DIRECTION::RIGHT: {
							std::cout << "▶";
						}

												  break;
						}
					}
					else if (object_manager::get_instance()->is_weapon_thrown() && xCoord == object_manager::get_instance()->get_thrown_weapon()->get_x_coord() && yCoord == object_manager::get_instance()->get_thrown_weapon()->get_y_coord() && mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
						set_color((int)COLOR::GREEN, (int)COLOR::LIGHT_YELLOW);

						int direction = object_manager::get_instance()->get_thrown_weapon()->get_direction();

						switch (direction) {
						case (int)DIRECTION::UP: {
							std::cout << "↑";
						}

											   break;

						case (int)DIRECTION::DOWN: {
							std::cout << "↓";
						}

												 break;

						case (int)DIRECTION::LEFT: {
							std::cout << "←";
						}

												 break;

						case (int)DIRECTION::RIGHT: {
							std::cout << "→";
						}

												  break;
						}
					}
					else {
						std::cout << "  ";
					}
				}
			}

									 break;

			case (int)CELL_TYPE::WALL: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::UNDISCOVERED) {
					set_color((int)COLOR::BLACK, (int)COLOR::BLACK);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::GRAY, (int)COLOR::GRAY);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::BLACK, (int)COLOR::YELLOW);
				}

				std::cout << "  ";
			}

									 break;

			case (int)CELL_TYPE::BLADE: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::UNDISCOVERED) {
					set_color((int)COLOR::BLACK, (int)COLOR::BLACK);

					std::cout << "  ";
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::BLUE, (int)COLOR::GRAY);

					std::cout << "■";
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::LIGHT_BLUE, (int)COLOR::YELLOW);

					std::cout << "■";
				}
			}

									  break;
			}
		}
	}
}

void maze::render_maze_once() {
	bool isGrieverRendered = false;
	int playerXCoord, playerYCoord, startXCoord, endXCoord, startYCoord, endYCoord, renderY = 0;
	playerXCoord = object_manager::get_instance()->get_runner()->get_x_coord();
	playerYCoord = object_manager::get_instance()->get_runner()->get_y_coord();
	startXCoord = std::clamp(playerXCoord - (RENDER_SIDE / 2 - 1), 0, MAZE_SIDE - RENDER_SIDE);
	endXCoord = std::clamp(playerXCoord + RENDER_SIDE / 2, RENDER_SIDE - 1, MAZE_SIDE - 1);
	startYCoord = std::clamp(playerYCoord - (RENDER_SIDE / 2 - 1), 0, MAZE_SIDE - RENDER_SIDE);
	endYCoord = std::clamp(playerYCoord + RENDER_SIDE / 2, RENDER_SIDE - 1, MAZE_SIDE - 1);

	for (int yCoord = startYCoord; yCoord <= endYCoord; ++yCoord) {
		go_to_xy(0, renderY++);

		for (int xCoord = startXCoord; xCoord <= endXCoord; ++xCoord) {
			switch (mazeData[yCoord][xCoord].first) {
			case (int)CELL_TYPE::GLADE: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::RED, (int)COLOR::GRAY);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::LIGHT_RED, (int)COLOR::YELLOW);
				}

				std::cout << "■";
			}

									  break;

			case (int)CELL_TYPE::ROAD: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::UNDISCOVERED) {
					set_color((int)COLOR::BLACK, (int)COLOR::BLACK);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::LIGHT_GRAY, (int)COLOR::LIGHT_GRAY);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::BLACK, (int)COLOR::LIGHT_YELLOW);

					for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
						if (!object_manager::get_instance()->get_griever(i)->is_dead()) {
							if (xCoord == object_manager::get_instance()->get_griever(i)->get_x_coord() && yCoord == object_manager::get_instance()->get_griever(i)->get_y_coord()) {
								std::cout << "※";

								isGrieverRendered = true;
							}
						}
					}
				}

				if (isGrieverRendered) {
					isGrieverRendered = false;
				}
				else {
					if (xCoord == playerXCoord && yCoord == playerYCoord) {
						int direction = object_manager::get_instance()->get_runner()->get_last_direction();

						switch (direction) {
						case (int)DIRECTION::UP: {
							std::cout << "▲";
						}

											   break;

						case (int)DIRECTION::DOWN: {
							std::cout << "▼";
						}

												 break;

						case (int)DIRECTION::LEFT: {
							std::cout << "◀";
						}

												 break;

						case (int)DIRECTION::RIGHT: {
							std::cout << "▶";
						}

												  break;
						}
					}
					else {
						std::cout << "  ";
					}
				}
			}

									 break;

			case (int)CELL_TYPE::WALL: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::UNDISCOVERED) {
					set_color((int)COLOR::BLACK, (int)COLOR::BLACK);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::GRAY, (int)COLOR::GRAY);
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::BLACK, (int)COLOR::YELLOW);
				}

				std::cout << "  ";
			}

									 break;

			case (int)CELL_TYPE::BLADE: {
				if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::UNDISCOVERED) {
					set_color((int)COLOR::BLACK, (int)COLOR::BLACK);

					std::cout << "  ";
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::DISCOVERED) {
					set_color((int)COLOR::BLUE, (int)COLOR::GRAY);

					std::cout << "■";
				}
				else if (mazeData[yCoord][xCoord].second == (int)CELL_STATE::IN_SIGHT) {
					set_color((int)COLOR::LIGHT_BLUE, (int)COLOR::YELLOW);

					std::cout << "■";
				}
			}

									  break;
			}
		}

		Sleep(50);
	}
}

void maze::render_black() {
	set_color((int)COLOR::BLACK, (int)COLOR::BLACK);

	for (int renderY = 0; renderY < 20; ++renderY) {
		go_to_xy(0, renderY);

		for (int renderX = 0; renderX < 50; ++renderX) {

			std::cout << ' ';
		}

		Sleep(50);
	}
}

void maze::generate_maze(int xCoord, int yCoord) {
	std::mt19937 gen(rd());

	std::vector<int> directions = { (int)DIRECTION::UP, (int)DIRECTION::DOWN, (int)DIRECTION::LEFT, (int)DIRECTION::RIGHT };

	std::shuffle(directions.begin(), directions.end(), gen);

	for (int i = 0; i < directions.size(); ++i) {
		if (directions[i] == (int)DIRECTION::UP) {
			if (yCoord > 2 && mazeData[yCoord - 2][xCoord].first == (int)CELL_TYPE::WALL) {
				for (int j = 0; j < 3; ++j) {
					mazeData[yCoord - 2 + j][xCoord].first = (int)CELL_TYPE::ROAD;
				}

				generate_maze(xCoord, yCoord - 2);
			}
		}
		else if (directions[i] == (int)DIRECTION::DOWN) {
			if (yCoord + 2 < MAZE_SIDE - 1 && mazeData[yCoord + 2][xCoord].first == (int)CELL_TYPE::WALL) {
				for (int j = 0; j < 3; ++j) {
					mazeData[yCoord + j][xCoord].first = (int)CELL_TYPE::ROAD;
				}

				generate_maze(xCoord, yCoord + 2);
			}
		}
		else if (directions[i] == (int)DIRECTION::LEFT) {
			if (xCoord > 2 && mazeData[yCoord][xCoord - 2].first == (int)CELL_TYPE::WALL) {
				for (int j = 0; j < 3; ++j) {
					mazeData[yCoord][xCoord - 2 + j].first = (int)CELL_TYPE::ROAD;
				}

				generate_maze(xCoord - 2, yCoord);
			}
		}
		else if (directions[i] == (int)DIRECTION::RIGHT) {
			if (xCoord + 2 < MAZE_SIDE - 1 && mazeData[yCoord][xCoord + 2].first == (int)CELL_TYPE::WALL) {
				for (int j = 0; j < 3; ++j) {
					mazeData[yCoord][xCoord + j].first = (int)CELL_TYPE::ROAD;
				}

				generate_maze(xCoord + 2, yCoord);
			}
		}
	}
}
