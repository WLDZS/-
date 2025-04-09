#ifndef PLAT_FORM_H
#define PLAT_FORM_H

#include <graphics.h>
#include "collision_box.h"
#include "collision_manager.h"
#include "vector2.h"
#include "camera.h"
#include "util.h"

class PlatForm
{
public:

	PlatForm(Vector2 position) :position(position) {
		collision_box.set_position(&this->position);
		
		CollisionManager::instance()->add_collision_box(&collision_box);
	};

public:

	void set_camera(Camera* camera) {
		this->camera = camera;
		collision_box.set_camera(camera);
	}

	void set_image(IMAGE* image) {
		this->image = image;
		size = Vector2(image->getwidth(), image->getheight());
		collision_box.set_size(Vector2(size.x, size.y));
	}

	void on_render() {
		static Rect rect = {
			position.x - size.x / 2, position.y - size.y / 2,
			size.x, size.y
		};
		putimage_ex(camera, image, &rect);
		collision_box.on_render();
	}

private:
	Camera* camera = nullptr;
	IMAGE* image = nullptr;
	CollisionBox collision_box;
	Vector2 size;
	Vector2 position;
	bool is_active = true;
};

#endif // PLAT_FORM_H