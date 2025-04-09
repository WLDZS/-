#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "collision_box.h"
#include "manager.h"
#include <vector>

class CollisionManager : public Manager<CollisionManager>
{
public:
	void add_collision_box(CollisionBox* collision_box);

	void on_update();

	void on_render();

private:
	std::vector<CollisionBox*> collision_box_pool;
};

#endif // COLLISION_MANAGER_H