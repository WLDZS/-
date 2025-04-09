#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "vector2.h"
#include "camera.h"
#include <functional>
#include <graphics.h>

class CollisionBox 
{
public:
	CollisionBox() = default;
	CollisionBox(Vector2* position, Vector2 size, Camera* camera) : size(size), position(position), camera(camera) {}
	~CollisionBox() = default;

public:

	void on_render() {
		if (!is_visible) return;

		const Vector2 cam_pos = camera->get_position();
		const Vector2 cam_size = camera->get_size();
		
		rectangle(position->x - size.x / 2 - (cam_pos.x - cam_size.x / 2), 
		    position->y - size.y / 2 - (cam_pos.y - cam_size.y / 2),
			position->x + size.x / 2 - (cam_pos.x - cam_size.x / 2),
			position->y + size.y / 2 - (cam_pos.y - cam_size.y / 2));
	}

	Vector2 get_position() const {
		return *position;
	}

	void set_position(Vector2* position) {
		this->position = position;
	}

	void set_size(Vector2 size) {
		this->size = size;
	}

	Vector2 get_size() const {
		return size;
	}

	void set_camera(Camera* camera) {
		this->camera = camera;
	}

	bool is_colliding(CollisionBox* other) const {
		if (!is_active || !other->is_active) return false;
		if (position->x + size.x / 2 < other->position->x - other->size.x / 2) return false;
		if (position->x - size.x / 2 > other->position->x + other->size.x / 2) return false;
		if (position->y + size.y / 2 < other->position->y - other->size.y / 2) return false;
		if (position->y - size.y / 2 > other->position->y + other->size.y / 2) return false;
		if (on_collision) on_collision();
		return true;
	}

	void set_on_collision(std::function<void()> on_collision) {
		this->on_collision = on_collision;
	}

private:
	Camera* camera = nullptr;
	Vector2 size;
	Vector2* position = nullptr;
	bool is_active = true;
	bool is_visible = true;
	std::function<void()> on_collision = nullptr;
};

#endif // COLLISION_BOX_H