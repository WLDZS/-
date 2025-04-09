#include "hornet_idle_state.h"
#include "hornet.h"

HornetIdleState::HornetIdleState(Hornet* hornet) : HornetStateMachine(hornet) {}

void HornetIdleState::on_enter() {
    if(is_inited == true) return;

    if (hornet->get_facing_dir() == Dir::Right) {
        current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkEndRight);
        current_animation->restart();
        current_animation->set_on_finished([this]() {
            current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetIdleRight);
            current_animation->restart();
        });
    }

    if (hornet->get_facing_dir() == Dir::Left) {
        current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkEndLeft);
        current_animation->restart();
        current_animation->set_on_finished([this]() {
            current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetIdleLeft);
            current_animation->restart();
        });
    }

    is_inited = true;
}

void HornetIdleState::on_input(ExMessage& msg) {
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

void HornetIdleState::on_update(double delta_time) {
    current_animation->on_update(delta_time);

    if (is_D_key_down) {
        hornet->get_velocity().x = hornet->WALK_SPEED;
        is_D_key_down = false;
        is_A_key_down = false;
        is_space_key_down = false;
        return;
    }
    if (is_A_key_down) {
        hornet->get_velocity().x = -hornet->WALK_SPEED;
        is_D_key_down = false;
        is_A_key_down = false;
        is_space_key_down = false;
        return;
    }
    if (is_space_key_down) {
        hornet->set_velocity(Vector2(0, hornet->JUMP_SPEED));
        is_D_key_down = false;
        is_A_key_down = false;
        is_space_key_down = false;
        return;
    }
    if (is_D_key_down == false && is_A_key_down == false)
        hornet->get_velocity().x = 0;
}

void HornetIdleState::on_render(Camera* camera) {
    current_animation->on_render(camera, hornet->get_position());
}

void HornetIdleState::on_exit() {
    is_inited = false;
}

Animation* HornetIdleState::get_animation() {
    return current_animation;
}