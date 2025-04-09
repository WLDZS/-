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

    const Vector2& get_position() const {
		return *position;
	}

	const Vector2& get_size() const {
		return size;
	}

	void set_target_position(Vector2* position) {
		this->position = position;
	}

private:
	Vector2 size = Vector2(1280, 720);
	Vector2* position = new Vector2(0, 0);
};

#endif // CAMERA_H