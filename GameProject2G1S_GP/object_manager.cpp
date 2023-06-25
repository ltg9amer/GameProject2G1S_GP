#include "object_manager.h"
#include "griever.h"
#include "runner.h"

object_manager* object_manager::instance = nullptr;

object_manager::object_manager() : thrownWeapon{ nullptr }, player{ nullptr } {
	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		grievers[i] = nullptr;
	}
}

object_manager::~object_manager() {

}

void object_manager::init() {
	player = new runner;

	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		grievers[i] = new griever;
	}
}

void object_manager::update() {
	player->update();

	for (int i = 0; i < MAZE_PATTERN_AMOUNT; ++i) {
		if (!grievers[i]->is_dead()) {
			grievers[i]->update();
		}
	}
}
