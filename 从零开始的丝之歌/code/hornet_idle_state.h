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
};
#endif // HORNET_IDLE_STATE_H