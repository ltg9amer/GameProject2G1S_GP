#include "console.h"

static HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

BOOL go_to_xy_test(int x, int y) {
	COORD cur = { x, y };

	return SetConsoleCursorPosition(hOut, cur);
}

void full_screen() {
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, NULL);
}

void go_to_xy(int x, int y) {
	COORD cur = { x, y };

	SetConsoleCursorPosition(hOut, cur);
}

void go_to_xy_player(int x, int y) {
	COORD cur = { x * 2, y };

	SetConsoleCursorPosition(hOut, cur);
}

void cursor_set(bool vis, DWORD size) {
	CONSOLE_CURSOR_INFO info;

	info.bVisible = vis;
	info.dwSize = size;

	SetConsoleCursorInfo(hOut, &info);
}

void set_color(int color) {
	SetConsoleTextAttribute(hOut, (get_bg_color() << 4) | color);
}

void set_color(int color, int bgColor) {
	SetConsoleTextAttribute(hOut, (bgColor << 4) | color);
}

void font_size(UINT weight, UINT sizeX, UINT sizeY) {
	static CONSOLE_FONT_INFOEX font;

	font.cbSize = sizeof(font);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	GetCurrentConsoleFontEx(hout, false, &font);

	font.FontWeight = weight;
	font.dwFontSize.X = sizeX;
	font.dwFontSize.Y = sizeY;

	SetCurrentConsoleFontEx(hout, false, &font);
}

int get_color() {
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(hOut, &info);

	int color = info.wAttributes & 0xf;

	return color;
}

int get_bg_color() {
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(hOut, &info);

	int color = (info.wAttributes & 0xf) >> 4;

	return color;
}