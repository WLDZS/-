#include "hornet_jump_state.h"
#include "hornet.h"
#include <iostream>

HornetJumpState::HornetJumpState(Hornet* hornet) : HornetStateMachine(hornet) {}

void HornetJumpState::on_enter() {

	if (is_inited == true) return;

	if (hornet->get_facing_dir() == Dir::Right) {
		current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetJumpRight);
		current_animation->restart();
	}
	if (hornet->get_facing_dir() == Dir::Left) {
		current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetJumpLeft);
		current_animation->restart();
	}

	is_inited = true;
}

void HornetJumpState::on_input(ExMessage& msg) {

}

void HornetJumpState::on_update(double delta_time) {
	current_animation->on_update(delta_time);
	if (hornet->get_facing_dir() != hornet->get_last_facing_dir()) {
		if (hornet->get_facing_dir() == Dir::Right) {
			int frame_idx = current_animation->get_frame_index();
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetJumpRight);
			current_animation->set_frame_index(frame_idx);
		}
		if (hornet->get_facing_dir() == Dir::Left) {
			int frame_idx = current_animation->get_frame_index();
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetJumpLeft);
			current_animation->set_frame_index(frame_idx);
		}
	}
}

void HornetJumpState::on_render(Camera* camera) {
	current_animation->on_render(camera, hornet->get_position());
}

void HornetJumpState::on_exit() {
	is_inited = false;
}

Animation* HornetJumpState::get_animation() {
	return current_animation;
}