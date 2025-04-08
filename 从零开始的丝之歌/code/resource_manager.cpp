#include "resource_manager.h"
#include "animation.h"

void ResourceManager::load_resources() {
	load_image(_T("resources/background/background.png"), IMAGEID::Background);

	load_animation(_T("resources/charactor/hornet/Idle/%d.png"), AnimationID::HornetIdleRight, 6);
	load_animation(AnimationID::HornetIdleLeft, animation_pool[AnimationID::HornetIdleRight]);
	load_animation(_T("resources/charactor/hornet/Walk/%d.png"), AnimationID::HornetWalkRight, 8);
	load_animation(AnimationID::HornetWalkLeft, animation_pool[AnimationID::HornetWalkRight]);
	load_animation(_T("resources/charactor/hornet/WalkStart/%d.png"), AnimationID::HornetWalkStartRight, 6);
	load_animation(AnimationID::HornetWalkStartLeft, animation_pool[AnimationID::HornetWalkStartRight]);
	load_animation(_T("resources/charactor/hornet/WalkEnd/%d.png"), AnimationID::HornetWalkEndRight, 3);
	load_animation(AnimationID::HornetWalkEndLeft, animation_pool[AnimationID::HornetWalkEndRight]);
	load_animation(_T("resources/charactor/hornet/Turn/%d.png"), AnimationID::HornetTurnRight, 3);
	load_animation(AnimationID::HornetTurnLeft, animation_pool[AnimationID::HornetTurnRight]);
	load_animation(_T("resources/charactor/hornet/Jump/%d.png"), AnimationID::HornetJumpRight, 6);
	load_animation(AnimationID::HornetJumpLeft, animation_pool[AnimationID::HornetJumpRight]);
	load_animation(_T("resources/charactor/hornet/Fall/%d.png"), AnimationID::HornetFallRight, 4);
	load_animation(AnimationID::HornetFallLeft, animation_pool[AnimationID::HornetFallRight]);

	init_animation();
}

void ResourceManager::load_animation(LPCTSTR path, AnimationID id, int num) {
	animation_pool[id] = new Animation();
	animation_pool[id]->load(path, num);
}

void ResourceManager::load_animation(AnimationID id, Animation* anim) {
	animation_pool[id] = new Animation();
	animation_pool[id]->load(anim->get_frame_pool());
}

void ResourceManager::load_image(LPCTSTR path, IMAGEID id) {
	image_pool[id] = new IMAGE();
	loadimage(image_pool[id], path);
}

Animation* ResourceManager::find_animation(AnimationID id) {
	return animation_pool[id];
}

IMAGE* ResourceManager::find_image(IMAGEID id) {
	return image_pool[id];
}

void ResourceManager::init_animation() {
	Animation* anim = nullptr;

	anim = animation_pool[AnimationID::HornetIdleRight];
	anim->set_interval(0.13);

	anim = animation_pool[AnimationID::HornetIdleLeft];
	anim->set_interval(0.13);

	anim = animation_pool[AnimationID::HornetWalkRight];
	anim->set_interval(0.10);

	anim = animation_pool[AnimationID::HornetWalkLeft];
	anim->set_interval(0.10);

	anim = animation_pool[AnimationID::HornetWalkStartRight];
	anim->set_interval(0.07);

	anim = animation_pool[AnimationID::HornetWalkStartLeft];
	anim->set_interval(0.07);

	anim = animation_pool[AnimationID::HornetWalkEndRight];
	anim->set_interval(0.10);

	anim = animation_pool[AnimationID::HornetWalkEndLeft];
	anim->set_interval(0.10);

	anim = animation_pool[AnimationID::HornetTurnRight];
	anim->set_interval(0.05);

	anim = animation_pool[AnimationID::HornetTurnLeft];
	anim->set_interval(0.05);

	anim = animation_pool[AnimationID::HornetJumpRight];
	anim->set_interval(0.13);
	anim->set_is_loop(false);

	anim = animation_pool[AnimationID::HornetJumpLeft];
	anim->set_interval(0.13);
	anim->set_is_loop(false);

	anim = animation_pool[AnimationID::HornetFallRight];
	anim->set_interval(0.10);

	anim = animation_pool[AnimationID::HornetFallLeft];
	anim->set_interval(0.10);
}