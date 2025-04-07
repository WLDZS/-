#include "game_manager.h"
#include "resource_manager.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <string>
#include <graphics.h>
//test
#include "animation.h"
#include "hornet.h"

GameManager::GameManager() {
	init();
}

void GameManager::init() {
	ResourceManager::instance()->load_resources();

	player = new Hornet();
	camera = new Camera();

	player->set_camera(camera);
	camera->set_target_position(&player->get_position());
}

int GameManager::run(int argc, char* argv[]) {

	ExMessage msg;

	HWND hwnd = initgraph(1280, 720, EX_SHOWCONSOLE);

	const std::chrono::nanoseconds frame_duration(1000000000 / 100000000000);   // 60 FPS
	
	BeginBatchDraw();

	while (true) {

		static auto last_tick = std::chrono::steady_clock::now();

		while (peekmessage(&msg)) 
			on_input(msg);

		auto frame_start = std::chrono::steady_clock::now();
		std::chrono::duration<double> delta_time = std::chrono::duration<double>(frame_start - last_tick);

		on_update(delta_time.count());

		cleardevice();

		on_render();

		FlushBatchDraw();

		last_tick = frame_start;

	    std::chrono::nanoseconds sleep_duration = frame_duration - (std::chrono::steady_clock::now() - frame_start);

		auto sleep_start = std::chrono::steady_clock::now();
		if (sleep_duration > std::chrono::nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);
		auto sleep_end = std::chrono::steady_clock::now();
		//std::cout << "Sleep time: " << std::chrono::duration<float>(sleep_end - sleep_start).count() << "s" << std::endl;

		FPS_counter(delta_time.count());
	}

	EndBatchDraw();

	return 0;
}

void GameManager::on_input(ExMessage& msg) {
	player->on_input(msg);
}

void GameManager::on_update(double delta_time) {
	player->on_update(delta_time);
	camera->on_update();
}

void GameManager::on_render() {
	static const Rect rect = { 0, 0, 1280, 720 };
	putimage_ex(camera, ResourceManager::instance()->find_image(IMAGEID::Background), &rect);
	player->on_render();
}

void GameManager::FPS_counter(double delta_time) {
	static int FPS_count = 0;
	static double passed_time = 0.0;

	FPS_count++;
	passed_time += delta_time;

	if (passed_time >= 1) {
		std::cout << "FPS: " << FPS_count << std::endl;
		FPS_count = 0;
		passed_time -= 1;
	}
}