#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <Windows.h>
#include "console.h"
#include "maze_manager.h"
#include "start.h"

void render_title() {
	int prevMode = _setmode(_fileno(stdout), _O_U16TEXT);

	std::wcout << std::endl << std::endl;
	std::wcout << L"        ╔╦╗╔═╗╔═╗╔═╗  ╦═╗╦ ╦╔╗╔╔╗╔╔═╗╦═╗" << std::endl;
	std::wcout << L"        ║║║╠═╣╔═╝║╣   ╠╦╝║ ║║║║║║║║╣ ╠╦╝" << std::endl;
	std::wcout << L"        ╩ ╩╩ ╩╚═╝╚═╝  ╩╚═╚═╝╝╚╝╝╚╝╚═╝╩╚═" << std::endl;
	std::wcout << L"                    ╔╦╗╦ ╦╔═╗           " << std::endl;
	std::wcout << L"                     ║ ╠═╣║╣            " << std::endl;
	std::wcout << L"                     ╩ ╩ ╩╚═╝           " << std::endl;
	std::wcout << L"               ╔═╗╔═╗ ╦ ╦╔═╗╦═╗╔═╗      " << std::endl;
	std::wcout << L"               ╚═╗║═╬╗║ ║╠═╣╠╦╝║╣       " << std::endl;
	std::wcout << L"               ╚═╝╚═╝╚╚═╝╩ ╩╩╚═╚═╝      " << std::endl;

	int curMode = _setmode(_fileno(stdout), prevMode);
}

void render_info() {
	system("cls");

	int prevMode = _setmode(_fileno(stdout), _O_U16TEXT);

	std::wcout << std::endl << std::endl;
	std::wcout << L"                ╔╦╗╔═╗╔╗╔╦ ╦╔═╗╦  " << std::endl;
	std::wcout << L"                ║║║╠═╣║║║║ ║╠═╣║  " << std::endl;
	std::wcout << L"                ╩ ╩╩ ╩╝╚╝╚═╝╩ ╩╩═╝" << std::endl;

	int curMode = _setmode(_fileno(stdout), prevMode);

	go_to_xy(17, 9);

	std::cout << "W";

	go_to_xy(9, 10);

	std::cout << "이동: A S D         무기 발사: F";

	go_to_xy(9, 15);

	std::cout << "선택: Space       게임 종료: Esc";

	while (key_check() != (int)KEY::SPACE);
}

int render_menu() {
	std::string menuText[3] = { "START", "MANUAL", "QUIT" };
	int x = 22, y = 13;

	go_to_xy(x, y);

	std::cout << menuText[0];

	set_color((int)COLOR::GRAY, (int)COLOR::BLACK);
	go_to_xy(x, y + 2);

	std::cout << menuText[1];

	go_to_xy(x, y + 4);

	std::cout << menuText[2];

	set_color((int)COLOR::RED, (int)COLOR::BLACK);
	go_to_xy(x - 3, y);

	std::cout << "▶";

	go_to_xy(x + 6, y);

	std::cout << "◀";

	while (true) {
		int key = key_check();

		switch (key) {
		case (int)KEY::UP: {
			if (y > 13) {
				set_color((int)COLOR::GRAY, (int)COLOR::BLACK);
				go_to_xy(x - 3, y);

				std::cout << "   " << menuText[(y - 13) / 2] << "   ";

				y -= 2;

				set_color((int)COLOR::RED, (int)COLOR::BLACK);
				go_to_xy(x - 3, y);

				std::cout << "▶ " << menuText[(y - 13) / 2] << " ◀";
			}
		}

						 break;

		case (int)KEY::DOWN: {
			if (y < 17) {
				set_color((int)COLOR::GRAY, (int)COLOR::BLACK);
				go_to_xy(x - 3, y);

				std::cout << "   " << menuText[(y - 13) / 2] << "   ";

				y += 2;

				set_color((int)COLOR::RED, (int)COLOR::BLACK);
				go_to_xy(x - 3, y);

				std::cout << "▶ " << menuText[(y - 13) / 2] << " ◀";
			}
		}

						   break;

		case (int)KEY::SPACE: {
			return (y - 13) / 2;
		}
		}
	}
}

int key_check() {
	int key = _getch();

	if (key == 224)
	{
		key = _getch();

		switch (key)
		{
		case 72:
			return (int)KEY::UP;

		case 80:
			return (int)KEY::DOWN;

		default:
			break;
		}
	}
	else if (key == 32)
	{
		return (int)KEY::SPACE;
	}

	return (int)KEY::SPACE + 1;
}
