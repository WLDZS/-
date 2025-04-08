#ifndef HORNET_JUMP_STATE_H
#define HORNET_JUMP_STATE_H

#include "hornet_state_machine.h"

class HornetJumpState : public HornetStateMachine
{
public:
	HornetJumpState(Hornet* hornet);
public:
	void on_enter() override;
	void on_input(ExMessage& msg) override;
	void on_update(double delta_time) override;
	void on_render(Camera* camera) override;
	void on_exit() override;

	Animation* get_animation() override;
private:
	bool is_A_key_down = false;
	bool is_D_key_down = false;
};

#endif // HORNET_JUMP_STATE_H