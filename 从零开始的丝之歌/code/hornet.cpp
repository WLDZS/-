#include "hornet.h"
#include "resource_manager.h"
#include <iostream>

Hornet::Hornet() {
	state_pool[HornetStateID::Idle] = new HornetIdleState(this);
	current_state = state_pool[HornetStateID::Idle];
	current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetIdleRight);
	position = Vector2(0, 0);
}

void Hornet::on_update(double delta_time) {
	update_animation();
	current_animation->on_update(delta_time);
	collision_box.on_update(position);

	//∫·œÚ“∆∂Ø
	if (is_right_key_down)
		velocity.x = SPEED;
	if (is_left_key_down) 
		velocity.x = -SPEED;
	if (!is_right_key_down &&!is_left_key_down)
		velocity.x = 0;

	//Ã¯‘æ
    if (is_jump_key_down && is_on_ground) {
		velocity.y = -JUMP_SPEED;
		is_jump_key_down = false;
	}
	if (position.y + size.y / 2 < 720 && is_on_ground)
		is_on_ground = false;
	if (position.y + size.y / 2 >= 720 && !is_on_ground) {
		position.y = 720 - size.y / 2;
		velocity.y = 0;
		is_on_ground = true;
	}
	if(!is_on_ground)
		velocity.y += GRAVITY_SPEED * delta_time;

	position += velocity * delta_time;

}

void Hornet::on_render() {
	current_animation->on_render(camera, position);
	collision_box.on_render(camera);
}

void Hornet::on_input(ExMessage& msg) {
	switch (msg.message) {
		case WM_KEYDOWN:
			switch (msg.vkcode) {
			case 0x44: // D
				is_right_key_down = true;
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkRight);
				break;
			case 0x41: // A
				is_left_key_down = true;
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkLeft);
				break;
			case 0x57: // W
				is_jump_key_down = true;
				break;
			default:
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode) {
			case 0x44: // D
				is_right_key_down = false;
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetIdleRight);
				break;
			case 0x41: // A
				is_left_key_down = false;
				current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetIdleLeft);
				break;
			default:
				break;
			}
			break;
		default:
			break;
	}
}

void Hornet::update_animation() {

}

Vector2& Hornet::get_position() {
	return position;
}

void Hornet::set_camera(Camera* camera) {
	this->camera = camera;
}