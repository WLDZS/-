#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "vector2.h"
#include "camera.h"
#include <graphics.h>

class CollisionBox 
{
public:
	CollisionBox(Vector2 position, Vector2 size) : size(size), position(position) {}
	~CollisionBox() = default;

public:

	void on_update(Vector2 position) {
		this->position = position;
	}

	void on_render(Camera* camera) {
		if (!is_visible) return;

		const Vector2 cam_pos = camera->get_position();
		const Vector2 cam_size = camera->get_size();
		
		rectangle(position.x - size.x / 2 - (cam_pos.x - cam_size.x / 2), 
			position.y - size.y / 2 - (cam_pos.y - cam_size.y / 2),
			position.x + size.x / 2 - (cam_pos.x - cam_size.x / 2), 
			position.y + size.y / 2 - (cam_pos.y - cam_size.y / 2));
	}

	void on_render() {
		if (!is_visible) return;

		rectangle(position.x - size.x / 2, position.y - size.y / 2, 
			position.x + size.x / 2, position.y + size.y / 2);
	}

private:
	Vector2 size;
	Vector2 position;
	bool is_active = true;
	bool is_visible = true;
};

#endif // COLLISION_BOX_H