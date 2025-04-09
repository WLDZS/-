#include <queue>
#include <list>
#include <algorithm>
#include "collision_manager.h"

void CollisionManager::add_collision_box(CollisionBox* collision_box) {
    collision_box_pool.push_back(collision_box);
    std::sort(collision_box_pool.begin(), collision_box_pool.end(),
        [](const CollisionBox* a, const CollisionBox* b) {
            return a->get_position().x < b->get_position().x;
        });
}

void CollisionManager::on_update() {
    for (auto& collision_box : collision_box_pool) {
        for (auto& other_collision_box : collision_box_pool) {
            if (collision_box == other_collision_box) 
                continue;
            collision_box->is_colliding(other_collision_box);
        }
    }
}

void CollisionManager::on_render() {

}