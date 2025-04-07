#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "manager.h"
#include "timer.h"
#include "player.h"
#include "camera.h"
#include <graphics.h>

class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:

	int run(int argc, char* argv[]);

	void on_input(ExMessage& msg);

	void on_update(double delta_time);

	void on_render();

	void FPS_counter(double delta_time);

	void init();

protected:
	GameManager();

	~GameManager() = default;

private:
	Player *player = nullptr;
	Camera *camera = nullptr;
};

#endif // GAME_MANAGER_H
