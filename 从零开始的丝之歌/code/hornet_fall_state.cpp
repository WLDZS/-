#include "hornet_fall_state.h"
#include "hornet.h"
#include <iostream>

HornetFallState::HornetFallState(Hornet* hornet) : HornetStateMachine(hornet) {}

void HornetFallState::on_enter() {

	if (is_inited == true) return;

	if (hornet->get_dir() == Dir::Right) {
		current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetFallRight);
		current_animation->restart();
	}
	if (hornet->get_dir() == Dir::Left) {
		current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetFallLeft);
		current_animation->restart();
	}

	is_inited = true;
}

void HornetFallState::on_input(ExMessage& msg) {

}

void HornetFallState::on_update(double delta_time) {
	current_animation->on_update(delta_time);
	if (hornet->get_dir() != hornet->get_last_dir()) {
		if (hornet->get_dir() == Dir::Right) {
			int frame_idx = current_animation->get_frame_index();
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetFallRight);
			current_animation->set_frame_index(frame_idx);
		}
		if (hornet->get_dir() == Dir::Left) {
			int frame_idx = current_animation->get_frame_index();
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetFallLeft);
			current_animation->set_frame_index(frame_idx);
		}
	}
}

void HornetFallState::on_render(Camera* camera) {
	current_animation->on_render(camera, hornet->get_position());
}

void HornetFallState::on_exit() {
	is_inited = false;
}

Animation* HornetFallState::get_animation() {
	return current_animation;
}