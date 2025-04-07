#include "hornet_idle_state.h"
#include "hornet.h"

HornetIdleState::HornetIdleState(Hornet* hornet) : HornetStateMachine(hornet) {}

void HornetIdleState::on_enter() {
    state_animation = ResourceManager::instance()->find_animation(AnimationID::HornetIdleRight);
}

void HornetIdleState::on_input(ExMessage& msg) {

}

void HornetIdleState::on_update(double delta_time) {
    state_animation->on_update(delta_time);
}

void HornetIdleState::on_render(Camera* camera) {
    state_animation->on_render(camera, hornet->get_position());
}

void HornetIdleState::on_exit() {

}

Animation* HornetIdleState::get_animation() {
    return state_animation;
}