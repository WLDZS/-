#ifndef HORNET_H
#define HORNET_H

#include <unordered_map>
#include "player.h"
#include "collision_box.h"
#include "hornet_idle_state.h"
#include "hornet_walk_state.h"
#include "hornet_jump_state.h"
#include "hornet_fall_state.h"

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
	void set_position(const Vector2& pos) override;
	Vector2& get_velocity() override;
	void set_velocity(const Vector2& vel) override;
	void set_camera(Camera* camera) override;
	Dir get_dir() override;
	void set_dir(Dir dir) override;
	Dir get_last_dir() override;
	void set_last_dir(Dir dir) override;
private:
	void switch_state(HornetStateID state_id);
private:
	const double RUSH_SPEED = 150;
	const double WALK_SPEED = 300;
	const double JUMP_SPEED = 800;
	const double GRAVITY_SPEED = 1100;
private:
	Vector2 size = Vector2(50, 160);
	CollisionBox collision_box = CollisionBox(position, size);
	HornetStateMachine* current_state = nullptr;
	StatePool state_pool;
private:
	bool is_attacking = false;
	bool is_attack_cd_comp = true;

	bool is_A_key_down = false;
	bool is_D_key_down = false;
	bool is_space_key_down = false;

	bool is_on_ground = false;
};

#endif // HORNET_H