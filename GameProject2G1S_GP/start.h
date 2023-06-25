#pragma once

enum class KEY {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE
};

void render_title();

void render_info();

int render_menu();

int key_check();

