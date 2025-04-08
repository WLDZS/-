#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "manager.h"
#include "animation.h"
#include <unordered_map>
#include <graphics.h>
#include <string>
#include "player.h"

enum class AnimationID
{
	HornetIdleRight,
	HornetIdleLeft,
	HornetWalkRight,
	HornetWalkLeft,
	HornetWalkStartRight,
	HornetWalkStartLeft,
	HornetWalkEndRight,
	HornetWalkEndLeft,
	HornetTurnRight,
	HornetTurnLeft,
	HornetJumpRight,
	HornetJumpLeft,
	HornetFallRight,
	HornetFallLeft

};

enum class IMAGEID
{
	Background,
};

class ResourceManager : public Manager<ResourceManager>
{
	friend class Manager<ResourceManager>;
public:

	using AnimationPool = std::unordered_map<AnimationID, Animation*>;
	using ImagePool = std::unordered_map<IMAGEID, IMAGE*>;

public:

	void load_resources();

	Animation* find_animation(AnimationID id);
	IMAGE* find_image(IMAGEID id);

private:
	AnimationPool animation_pool;
	ImagePool image_pool;
private:
	void load_animation(LPCTSTR path, AnimationID id, int num);
	void load_animation(AnimationID id, Animation* anim);
	void load_image(LPCTSTR path, IMAGEID id);
    void init_animation();
};

#endif // RESOURCE_MANAGER_H
