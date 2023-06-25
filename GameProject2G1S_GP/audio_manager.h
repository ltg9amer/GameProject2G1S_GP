#pragma once
#include "define.h"

class audio_manager{
	static audio_manager* instance;

	audio_manager();

	~audio_manager();

public:
	static audio_manager* get_instance() {
		if (instance == nullptr) {
			instance = new audio_manager;
		}

		return instance;
	}

	static void destroy_instance() {
		if (instance) {
			delete instance;

			instance = nullptr;
		}
	}

	void init();

	void play_bgm() {
		PlaySound("Into the Maze.wav", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}

	void stop_bgm() {
		PlaySound(0, 0, 0);
	}
};

