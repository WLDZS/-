#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <iostream>

class Timer
{
public:
	void restart() {
		pass_time = 0.0f;
		shotted = false;
	}

	void set_wait_time(double wait_time) {
		this->wait_time = wait_time;
	}

	void set_one_shot(bool oneShot) {
		this->one_shot = oneShot;
	}

	void pause() {
		paused = true;
	}

	void resume() {
		paused = false;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	void on_update(double delta_time) {
		if (paused) return;
		pass_time += delta_time;
		if (pass_time >= wait_time) {
			bool can_shot = (!one_shot || (!shotted && one_shot));
			if (can_shot) {
				shotted = true;
				if (!(callback == nullptr)) 
					callback();
				pass_time -= wait_time;
			}
		}
	}

private:
	double pass_time = 0.0f;
	double wait_time = 0.0f;
	bool shotted = false;
	bool paused = false;
	bool one_shot = false;
    std::function<void()> callback = nullptr;
};

#endif // TIMER_H