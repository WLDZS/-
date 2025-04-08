#include "hornet_idle_state.h"
#include "hornet.h"

HornetIdleState::HornetIdleState(Hornet* hornet) : HornetStateMachine(hornet) {}

void HornetIdleState::on_enter() {
    if(is_inited == true) return;

    if (hornet->get_dir() == Dir::Right) {
        current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetWalkEndRight);
        current_animation->restart();
        current_animation->set_on_finished([this]() {
            current_animation = ResourceManager::instance()->find_animation(AnimationID::HornetIdleRight);
            current_animation->restart();
        });
    }

    if (hornet->get_dir() == Dir::Left) {
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

}

void HornetIdleState::on_update(double delta_time) {
    current_animation->on_update(delta_time);
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