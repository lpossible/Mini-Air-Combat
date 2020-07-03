#ifndef _LOAD_SCENE_H
#define _LOAD_SCENE_H
#include"cocos2d.h"
USING_NS_CC;
class LoadScene :public cocos2d::Scene
{
public:
	static Scene* createScene();
	bool init()override;
	CREATE_FUNC(LoadScene);
	void exchangeScene();
	void resourceLoading();
};
#endif // !_LOAD_SCENE_H
