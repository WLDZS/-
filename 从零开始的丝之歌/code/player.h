#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <graphics.h>
#include "vector2.h"
#include "animation.h"
#include "resource_manager.h"
#include "camera.h"

class Player 
{

public:
	Player() = default;
	~Player() = default;
public:
	virtual void on_update(double deltaTime) = 0;
	virtual void on_render() = 0;
	virtual void on_input(ExMessage& msg) = 0;
	virtual Vector2& get_position() = 0;
	virtual void set_camera(Camera* camera) = 0;
protected:
	virtual void update_animation() = 0;
protected:
	const double ATACK_CD = 0.5;
	const double SPEED = 300;
	const double GRAVITY_SPEED = 2000;
	const double JUMP_SPEED = 800;
protected:
	int hp = 5;
	Vector2 velocity = Vector2(0, 0);
	//ÖÐÐÄÎ»ÖÃ
	Vector2 position = Vector2(0, 0);
	Animation* current_animation = nullptr;

	Camera* camera = nullptr;

	bool is_attacking = false;
	bool is_attack_cd_comp = true;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_key_down = false;

	bool is_on_ground = false;
};

#endif // PLAYER_H