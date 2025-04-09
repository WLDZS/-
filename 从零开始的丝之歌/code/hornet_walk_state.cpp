#include "hornet_walk_state.h"
#include "hornet.h"

HornetWalkState::HornetWalkState(Hornet* hornet) : HornetStateMachine(hornet) {}

void HornetWalkState::on_enter() {

	if (is_inited == true) return;

	if (hornet->get_facing_dir() == Dir::Right) {
		if (hornet->get_last_facing_dir() == Dir::Right) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkStartRight);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkRight);
				current_animation->restart();
			});
		}
		if (hornet->get_last_facing_dir() == Dir::Left) {
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

	if (hornet->get_facing_dir() == Dir::Left) {
		if (hornet->get_last_facing_dir() == Dir::Left) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkStartLeft);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkLeft);
				current_animation->restart();
			});
		}
		if (hornet->get_last_facing_dir() == Dir::Right) {
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
	switch (msg.message) {
	case WM_KEYDOWN:
		switch (msg.vkcode) {
		case 0x44: // D
			hornet->set_facing_dir(Dir::Right);
			is_D_key_down = true;
			break;
		case 0x41: // A
			is_A_key_down = true;
			hornet->set_facing_dir(Dir::Left);
			break;
		case 0x20: // space
			is_space_key_down = true;
			break;
		default:
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
		default:
			break;
		}
		break;
	}
}

void HornetWalkState::on_update(double delta_time) {
	if (is_D_key_down) {
	    hornet->get_velocity().x = hornet->WALK_SPEED;
	}
	if (is_A_key_down) {
		hornet->get_velocity().x = -hornet->WALK_SPEED;
	}
	if (is_space_key_down) {
		hornet->set_velocity(Vector2(0, hornet->JUMP_SPEED));
	}
	if (is_D_key_down == false && is_A_key_down == false)
		hornet->get_velocity().x = 0;

	if (hornet->get_facing_dir() != hornet->get_last_facing_dir()) {
		if (hornet->get_facing_dir() == Dir::Right) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetTurnRight);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkRight);
				current_animation->restart();
			});
		}
		if (hornet->get_facing_dir() == Dir::Left) {
			current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetTurnLeft);
			current_animation->restart();
			current_animation->set_on_finished([this]() {
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkLeft);
				current_animation->restart();
			});
		}
	}


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