#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <iostream>
#include <graphics.h>
#include <functional>
#include "timer.h"
#include "util.h"
#include "vector2.h"
#include "camera.h"

class Animation
{
	using FramePool = std::vector<IMAGE>;
	using OnFinished = std::function<void()>;
public:

	Animation() {
		timer.set_callback([&]() {
			frame_index++;
			if (frame_index >= frame_pool.size()) {
				frame_index = is_loop ? 0 : frame_pool.size() - 1;
				if (on_finished)
					on_finished();
			}
		});
	}

	~Animation() = default;

public:
	void load(LPCTSTR path_template, int num) {
		TCHAR path[256];
		frame_pool.clear();
		frame_pool.resize(num);
		for (int i = 0; i < num; i++) {
			_stprintf_s(path, path_template, i);
			frame_pool[i] = IMAGE();
			IMAGE& img = frame_pool[i];
			loadimage(&img, path);
		}
	}

	void load(FramePool frame_pool) {
		this->frame_pool = frame_pool;
		//·­×ª
		for (auto& img_src : this->frame_pool) {
			DWORD* buffer_src = GetImageBuffer(&img_src);
			IMAGE img_dst;
			Resize(&img_dst, img_src.getwidth(), img_src.getheight());
			DWORD* buffer_dst = GetImageBuffer(&img_dst);
			for (int i = 0; i < img_src.getheight(); i++) {
				for (int j = 0; j < img_src.getwidth(); j++) {
					buffer_dst[i * img_dst.getwidth() + j] = buffer_src[i * img_src.getwidth() + (img_src.getwidth() - 1 - j)];
				}
			}
			img_src = img_dst;
		}
	}

	void restart() {
		frame_index = 0;
		timer.restart();
	}

	void on_update(double delta_time) {
		timer.on_update(delta_time);
	}

	void on_render(Camera* camera, Vector2 position) {
		this->position = position;
		const Rect rect_dst = { position.x - frame_pool[frame_index].getwidth() / 2,
			position.y - frame_pool[frame_index].getheight() / 2,
			frame_pool[frame_index].getwidth(), frame_pool[frame_index].getheight() };
		putimage_ex(camera, &frame_pool[frame_index], &rect_dst);
	}

	void set_interval(double wait_time) {
		timer.set_wait_time(wait_time);
	}

	void set_is_loop(bool is_loop) {
		this->is_loop = is_loop;
	}

	void set_on_finished(OnFinished on_finished) {
		this->on_finished = on_finished;
	}

	FramePool get_frame_pool() {
		return frame_pool;
	}

	int get_frame_index() {
		return frame_index;
	}

	void set_frame_index(int frame_index) {
		this->frame_index = frame_index;
	}

private:
	int frame_index = 0;
	Vector2 position = Vector2(0, 0);
	FramePool frame_pool;
	Timer timer;
	OnFinished on_finished = nullptr;
	bool is_loop = true;
};

#endif // ANIMATION_H