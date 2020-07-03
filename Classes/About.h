#ifndef _ABOUT_H
#define _ABOUT_H
#include"cocos2d.h"
USING_NS_CC;

class AboutScene :public Scene
{
public:
	bool init()override;
	CREATE_FUNC(AboutScene);
	bool backLabelTouched(Touch* touch, Event* event);
};

#endif // !_ABOUT_H

