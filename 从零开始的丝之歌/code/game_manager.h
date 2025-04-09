#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <graphics.h>
#include "manager.h"
#include "timer.h"
#include "player.h"
#include "camera.h"
#include "plat_form.h"


class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:

	int run(int argc, char* argv[]);

private:

	void on_input(ExMessage& msg);

	void on_update(double delta_time);

	void on_render();

	void FPS_counter(double delta_time);

	void init();

protected:
	GameManager();

	~GameManager() = default;
private:
	Player* player;
	Camera* camera;
	PlatForm* plat_form;
};	

#endif // GAME_MANAGER_H
