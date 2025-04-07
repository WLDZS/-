#ifndef CAMERA_H
#define CAMERA_H

#include "vector2.h"
#include <iostream>

class Camera
{
public:

	Camera() = default;

	~Camera() = default;

public:

	void reset() {
		position = Vector2(0, 0);
	}

	void on_update() {
		position = Vector2(target_position->x, target_position->y);
	}

	const Vector2& get_position() const {
		return position;
	}

	void set_target_position(Vector2* position) {
		this->target_position = position;
	}

	const Vector2& get_size() const {
		return size;
	}

private:
	Vector2 size = Vector2(1280, 720);
	Vector2 position = Vector2(0, 0);
	Vector2* target_position = nullptr;
};

#endif // CAMERA_H