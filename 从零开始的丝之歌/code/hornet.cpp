#include "hornet.h"
#include "resource_manager.h"
#include <iostream>

Hornet::Hornet() {
	state_pool[HornetStateID::Idle] = new HornetIdleState(this);
	state_pool[HornetStateID::Walk] = new HornetWalkState(this);
	state_pool[HornetStateID::Jump] = new HornetJumpState(this);
	state_pool[HornetStateID::Fall] = new HornetFallState(this);

	current_state = state_pool[HornetStateID::Idle];
	current_state->on_enter();

	position = Vector2(0, 0);
}

void Hornet::on_update(double delta_time) {
	collision_box.on_update(position);

	if (is_D_key_down) {
		velocity.x = WALK_SPEED;
	}
	if (is_A_key_down) {
		velocity.x = -WALK_SPEED;
	}
	if (!is_D_key_down && !is_A_key_down) {
		velocity.x = 0;
	}
	if (is_space_key_down && is_on_ground) {
		velocity.y = -JUMP_SPEED;
	}
	if (position.y + size.y / 2 < 720 && is_on_ground) {
		is_on_ground = false;
	}
	if (position.y + size.y / 2 >= 720 && !is_on_ground) {
		position.y = 720 - size.y / 2;
		is_on_ground = true;
		velocity.y = 0;
	}
	if (!is_on_ground) {
		velocity.y += GRAVITY_SPEED * delta_time;
	}

	position += velocity * delta_time;

	if(velocity.approach_x()) {
		if (current_state == state_pool[HornetStateID::Walk])
		    switch_state(HornetStateID::Idle);
	}

	if (!velocity.approach_x() && velocity.approach_y()) {
		if (current_state == state_pool[HornetStateID::Idle] || (dir != last_dir)) {
			switch_state(HornetStateID::Walk);
			last_dir = dir;
		}
	}
	if (is_on_ground && velocity.y <= 0) {
		if ((current_state == state_pool[HornetStateID::Walk] ||
			current_state == state_pool[HornetStateID::Idle]) && 
			is_space_key_down)
			switch_state(HornetStateID::Jump);
	}
	if (is_on_ground) {
		if (current_state == state_pool[HornetStateID::Fall])
			switch_state(HornetStateID::Idle);
	}
	if (!is_on_ground && velocity.y > 0) {
		if(current_state != state_pool[HornetStateID::Fall])
		switch_state(HornetStateID::Fall);
	}
	current_state->on_update(delta_time);
}

void Hornet::on_render() {
	/*collision_box.on_render(camera);*/
	current_state->on_render(camera);
}

void Hornet::on_input(ExMessage& msg) {
	switch (msg.message) {
	case WM_KEYDOWN:
		switch (msg.vkcode) {
		case 0x44: // D
			 is_D_key_down = true;
			 is_A_key_down = false;
			 last_dir = dir;
			 dir = Dir::Right;
			break;
		case 0x41: // A
			is_A_key_down = true;
			is_D_key_down = false;
			last_dir = dir;
			dir = Dir::Left;
			break;
		case 0x20: // space
			is_space_key_down = true;
			break;
		case 0x53: // S
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode) {
		case 0x44: // D
			is_D_key_down = false;
			break;
		case 0x41: // A
			is_A_key_down = false;
			break;
		case 0x20: // space
			is_space_key_down = false;
			break;
		case 0x53: // S
			break;
		}
		break;
	}
	current_state->on_input(msg);
}


Vector2& Hornet::get_position() {
	return position;
}

void Hornet::set_position(const Vector2& position) {
	this->position = position;
}

Vector2& Hornet::get_velocity() {
	return velocity;
}

void Hornet::set_velocity(const Vector2& velocity) {
	this->velocity = velocity;
}

void Hornet::set_camera(Camera* camera) {
	this->camera = camera;
}

Dir Hornet::get_dir() {
	return dir;
}

void Hornet::set_dir(Dir dir) {
	this->dir = dir;
}

Dir Hornet::get_last_dir() {
	return last_dir;
}

void Hornet::set_last_dir(Dir last_dir) {
	this->last_dir = last_dir;
}

void Hornet::switch_state(HornetStateID state_id) {
	current_state->on_exit();
	current_state = state_pool[state_id];
	current_state->on_enter();
}