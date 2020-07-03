#ifndef _LOAD_SCENE_H_
#define _LOAD_SCENE_H_
#include"cocos2d.h"
#include"Option.h"
#include"About.h"
#include"AudioEngine.h"
#include"PlayScene.h"
#include"LevelOneScene.h"
using namespace experimental;
USING_NS_CC;
class MainScene :public Scene
{
public:
	CREATE_FUNC(MainScene);
	static Scene* createScene();
	bool init()override;
	void menuNewCallback(Ref* pSender);
	void menuOptionCallback(Ref* pSender);
	void menuAboutCallback(Ref* pSender);
};
#endif // !#_LOAD_SCENE_H

