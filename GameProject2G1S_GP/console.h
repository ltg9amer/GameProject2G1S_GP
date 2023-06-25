#pragma once
#include<Windows.h>

enum class COLOR
{
	BLACK,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	LIGHT_GRAY,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	MINT,
	LIGHT_RED,
	LIGHT_VIOLET,
	LIGHT_YELLOW,
	WHITE
};

BOOL go_to_xy_test(int, int);

void full_screen();

void go_to_xy(int, int);

void go_to_xy_player(int, int);

void cursor_set(bool, DWORD);

void set_color(int);

void set_color(int, int);

void font_size(UINT, UINT, UINT);

int get_color();

int get_bg_color();

