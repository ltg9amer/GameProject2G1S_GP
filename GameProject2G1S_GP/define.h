#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#define MAZE_PATTERN_AMOUNT 8
#define MAZE_SIDE 99
#define RENDER_SIDE 20
#define VK_A 0x41
#define VK_D 0x44
#define VK_F 0x46
#define VK_S 0x53
#define VK_W 0x57

enum class DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class CELL_TYPE {
	GLADE,
	ROAD,
	WALL,
	BLADE
};

enum class CELL_STATE {
	UNDISCOVERED,
	DISCOVERED,
	IN_SIGHT
};
