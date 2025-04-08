#ifndef HORNET_STATE_MACHINE_H
#define HORNET_STATE_MACHINE_H

#include "resource_manager.h"

class Hornet;

enum class HornetStateID
{
	Idle,
	Walk,
	Jump,
	Fall
};

class HornetStateMachine
{	
public:
	HornetStateMachine(Hornet* hornet) : hornet(hornet) {};
public:

	virtual void on_enter() = 0;
	virtual void on_input(ExMessage& msg) = 0;
	virtual void on_update(double delta_time) = 0;
	virtual void on_render(Camera* camera) = 0;
	virtual void on_exit() = 0;

	virtual Animation* get_animation() = 0;

protected:
	Animation* current_animation = nullptr;
	Hornet* hornet;
	bool is_inited = false;
};

#endif // HORNET_STATE_MACHINE_H