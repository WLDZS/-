#ifndef CHARACTOR_H
#define CHARACTOR_H

#include "animation.h"
#include "Timer.h"
#include <string>

class Charactor
{
public:
    Character();
    ~Character();

    void decrease_hp();

    int get_hp() const
    {
        return hp;
    }

    void set_position(const Vector2& position)
    {
        this->position = position;
    }

    const Vector2& get_position() const
    {
        return position;
    }

    void set_velocity(const Vector2& velocity)
    {
        this->velocity = velocity;
    }

    const Vector2& get_velocity() const
    {
        return velocity;
    }

    Vector2 get_logic_center() const
    {
        return Vector2(position.x, position.y - logic_height / 2);
    }

    void set_gravity_enabled(bool flag)
    {
        enable_gravity = flag;
    }

    CollisionBox* get_hit_box()
    {
        return hit_box;
    }

    CollisionBox* get_hurt_box()
    {
        return hurt_box;
    }

    bool is_on_floor() const
    {
        return position.y >= FLOOR_Y;
    }

    float get_floor_y() const
    {
        return FLOOR_Y;
    }

    void make_invulnerable()
    {
        is_invulnerable = true;
        timer_invulnerable_status.restart();
    }

    virtual void on_input(const ExMessage& msg);
    virtual void on_update(float delta);
    virtual void on_render();
    virtual void on_hurt();

    void switch_state(const string& id);
    void set_animation(const string& id);

protected:
    const float FLOOR_Y = 620;                                      // 地板的垂直坐标
    const float GRAVITY = 980 * 2;                                  // 重力大小

protected:
    int hp = 10;                                                    // 角色生命值
    Vector2 position;                                               // 角色脚底位置
    Vector2 velocity;                                               // 角色速度
    float logic_height = 0;                                         // 角色的逻辑高度
    bool is_facing_left = true;                                     // 当前角色是否朝向左
    StateMachine state_machine;                                     // 角色状态机
    bool enable_gravity = true;                                     // 启用重力模拟
    bool is_invulnerable = false;                                   // 当前是否无敌
    Timer timer_invulnerable_blink;                                 // 无敌状态闪烁定时器
    Timer timer_invulnerable_status;                                // 无敌状态定时器
    bool is_blink_invisible = false;                                // 当前是否处于闪烁的不可见帧
    CollisionBox* hit_box = nullptr;                                // 攻击碰撞箱
    CollisionBox* hurt_box = nullptr;                               // 受击碰撞箱
    AnimationGroup* current_animation = nullptr;                    // 当前角色动画
};

#endif // CHARACTOR_H
