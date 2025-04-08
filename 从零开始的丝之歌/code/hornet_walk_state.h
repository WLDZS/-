#ifndef HORNET_WALK_STATE_H
#define HORNET_WALK_STATE_H

#include "hornet_state_machine.h"

class HornetWalkState : public HornetStateMachine
{
public:
	HornetWalkState(Hornet* hornet);
public:
	void on_enter() override;
	void on_input(ExMessage& msg) override;
	void on_update(double delta_time) override;
	void on_render(Camera* camera) override;
	void on_exit() override;

	Animation* get_animation() override;
private:
	const double WALK_SPEED = 300;
private:
	bool is_A_key_down = false;
	bool is_D_key_down = false;
};

#endif // HORNET_WALK_STATE_H
