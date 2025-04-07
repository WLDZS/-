#ifndef HORNET_H
#define HORNET_H

#include <unordered_map>
#include "player.h"
#include "collision_box.h"
#include "hornet_idle_state.h"

class Hornet : public Player
{
	using StatePool = std::unordered_map<HornetStateID, HornetStateMachine*>;
public:
	Hornet();
	~Hornet() = default;
public:
	void on_update(double deltaTime) override;
	void on_render() override;
	void on_input(ExMessage& msg) override;
	Vector2& get_position() override;
	void set_camera(Camera* camera) override;
private:
	void update_animation() override;
private:
	const double RUSH_SPEED = 150;
private:
	Vector2 size = Vector2(50, 160);
	CollisionBox collision_box = CollisionBox(position, size);
	HornetStateMachine* current_state = nullptr;
	StatePool state_pool;
};

#endif // HORNET_H