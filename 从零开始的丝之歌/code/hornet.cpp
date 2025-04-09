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

	collision_box.set_size(Vector2(40, 164));
	collision_box.set_position(&position);
	collision_box.set_on_collision([&]() {
		velocity.y = 0;
		is_on_ground = true;
	});

	CollisionManager::instance()->add_collision_box(&collision_box);
}

void Hornet::on_update(double delta_time) {

	if (current_state == state_pool[HornetStateID::Idle]) {
		if (!velocity.approach_x() && is_on_ground)
			switch_state(HornetStateID::Walk);
	}

	if (current_state == state_pool[HornetStateID::Walk]) {
		if(velocity.approach_x() && is_on_ground)
			switch_state(HornetStateID::Idle);
	}
	if (!is_on_ground)
	velocity.y += GRAVITY_SPEED * delta_time;

	position += velocity * delta_time;

	current_state->on_update(delta_time);
}

void Hornet::on_render() {
	collision_box.on_render();
	current_state->on_render(camera);
}

void Hornet::on_input(ExMessage& msg) {
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
	collision_box.set_camera(camera);
}

Dir Hornet::get_facing_dir() {
	return facing_dir;
}

void Hornet::set_facing_dir(Dir dir) {
	facing_dir = dir;
}

Dir Hornet::get_last_facing_dir() {
	return last_facing_dir;
}

void Hornet::set_last_facing_dir(Dir last_dir) {
	last_facing_dir = last_dir;
}

Dir Hornet::get_move_dir() {
	return move_dir;
}

void Hornet::set_move_dir(Dir dir) {
	move_dir = dir;
}

CollisionBox& Hornet::get_collision_box() {
	return collision_box;
}

void Hornet::switch_state(HornetStateID state_id) {
	current_state->on_exit();
	current_state = state_pool[state_id];
	current_state->on_enter();
}