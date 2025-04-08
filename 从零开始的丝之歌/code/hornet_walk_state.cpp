#include "hornet_walk_state.h"
#include "hornet.h"

HornetWalkState::HornetWalkState(Hornet* hornet) : HornetStateMachine(hornet) {}

void HornetWalkState::on_enter() {

	if (is_inited == true) return;

	if (hornet->get_dir() == Dir::Right) {
		if (hornet->get_last_dir() == Dir::Right) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkStartRight);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkRight);
				current_animation->restart();
			});
		}
		if (hornet->get_last_dir() == Dir::Left) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetTurnRight);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkStartRight);
				current_animation->restart();
				current_animation->set_on_finished([this]() {
					current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkRight);
					current_animation->restart();
				});
			});
		}
	}

	if (hornet->get_dir() == Dir::Left) {
		if (hornet->get_last_dir() == Dir::Left) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkStartLeft);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkLeft);
				current_animation->restart();
			});
		}
		if (hornet->get_last_dir() == Dir::Right) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetTurnLeft);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkStartLeft);
				current_animation->restart();
				current_animation->set_on_finished([this]() {
					current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkLeft);
					current_animation->restart();
				});
			});
		}
	}

	is_inited = true;
}

void HornetWalkState::on_input(ExMessage& msg) {

}

void HornetWalkState::on_update(double delta_time) {
	current_animation->on_update(delta_time);
}

void HornetWalkState::on_render(Camera* camera) {
	current_animation->on_render(camera, hornet->get_position());
}

void HornetWalkState::on_exit() {
	is_inited = false;
}

Animation* HornetWalkState::get_animation() {
	return current_animation;
}