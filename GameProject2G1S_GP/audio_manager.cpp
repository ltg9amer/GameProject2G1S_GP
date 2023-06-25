#pragma comment(lib, "winmm.lib")
#include "audio_manager.h"

audio_manager* audio_manager::instance = nullptr;

audio_manager::audio_manager() {

}

audio_manager::~audio_manager() {

}

void audio_manager::init() {
	play_bgm();
}
