#ifndef HORNET_IDLE_STATE_H
#define HORNET_IDLE_STATE_H

#include "hornet_state_machine.h"

class HornetIdleState : public HornetStateMachine
{
public:
	HornetIdleState(Hornet* hornet);
public:
	void on_enter() override;
	void on_input(ExMessage& msg) override;
	void on_update(double delta_time) override;
	void on_render(Camera* camera) override;
	void on_exit() override;
	
	Animation* get_animation() override;
private:
	bool is_attacking = false;
	bool is_attack_cd_comp = true;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_key_down = false;

	bool is_on_ground = false;
};
#endif // HORNET_IDLE_STATE_H