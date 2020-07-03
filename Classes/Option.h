#ifndef _OPTION_SCENE_H
#define _OPTION_SCENE_H
#include"cocos2d.h"
USING_NS_CC;

class OptionScene :public Scene
{
public:
	static Scene* createScene();
	CREATE_FUNC(OptionScene);
	bool init()override;
	Vec2 vec;
	bool backLabelTouched(Touch* touch, Event* event);
};
#endif // !

