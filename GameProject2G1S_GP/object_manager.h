#pragma once
#include "define.h"
#include "weapon.h"

class griever;

class runner;

class object_manager {
	static object_manager* instance;
	griever* grievers[MAZE_PATTERN_AMOUNT];
	runner* player;
	weapon* thrownWeapon;

	object_manager();

	~object_manager();

public:
	static object_manager* get_instance() {
		if (instance == nullptr) {
			instance = new object_manager;
		}

		return instance;
	}

	static void destroy_instance() {
		if (instance) {
			delete instance;

			instance = nullptr;
		}
	}

	griever* get_griever(int index) {
		return grievers[index];
	}

	runner* get_runner() {
		return player;
	}

	weapon* get_thrown_weapon() {
		return thrownWeapon;
	}

	bool is_weapon_thrown() {
		return thrownWeapon != nullptr;
	}

	void init();

	void update();

	void set_thrown_weapon(bool value) {
		if (value) {
			thrownWeapon = new weapon;
		}
		else {
			thrownWeapon = nullptr;
		}
	}
};

