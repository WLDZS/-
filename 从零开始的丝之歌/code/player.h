#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <graphics.h>
#include "vector2.h"
#include "animation.h"
#include "resource_manager.h"
#include "camera.h"


enum class Dir
{
	None,
	Left,
	Right,
	Up,
	Down,
};

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
	virtual void set_position(const Vector2& pos) = 0;
	virtual Vector2& get_velocity() = 0;
	virtual void set_velocity(const Vector2& vel) = 0;
	virtual void set_camera(Camera* camera) = 0;
	virtual Dir get_facing_dir() = 0;
	virtual void set_facing_dir(Dir dir) = 0;
	virtual Dir get_last_facing_dir() = 0;
	virtual void set_last_facing_dir(Dir dir) = 0;
	virtual void set_move_dir(Dir dir) = 0;
	virtual Dir get_move_dir() = 0;
protected:
	int hp = 5;
	Vector2 velocity = Vector2(0, 0);
	//ÖÐÐÄÎ»ÖÃ
	Vector2 position = Vector2(0, 0);

	Camera* camera = nullptr;
	Dir facing_dir = Dir::Right;  //0 left 1 right
	Dir last_facing_dir = Dir::Right;
	Dir move_dir = Dir::None;
};

#endif // !PLAYER_H