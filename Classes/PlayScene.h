#ifndef _PLAY_SCENE_H
#define _PLAY_SCENE_H
#include"cocos2d.h"
#include"EnemyBulletSprite.h"
#include<map>
USING_NS_CC;
class PlayScene:public Scene
{
private:
	//添加键盘点击map
	std::map<EventKeyboard::KeyCode, bool> keymap;
	//添加我方飞机子弹vector
	cocos2d::Vector<Sprite*> Bulletvector;
	//添加敌机Vector
	Vector<Sprite*> Enemyvector;
	//击中特效
	Vector<Sprite*> HitSpriteVector;
	//敌机子弹vector
	Vector<EnemyBulletSprite*> EnemyBulletVector;
	//主机状态切换
	bool flag = true;
	//地图偏量
	int offset = 636;
	//背景图
	Sprite* bgSprite;
	//主机触发事件
	EventListenerKeyboard* listener;
	//分数设置
	int score = 0;
	Label* scoreLabel=nullptr;
	//
	SpriteFrame* enemyBulletFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("W2.png");
public:
	bool init()override;
	CREATE_FUNC(PlayScene);
	//添加对键盘事件导致的位置更新
	void updatePlanePosition(float dt);
	void updatePlaneStatus(float dt);
	void updateBgStatus(float dt);
	void onKeyPressed(EventKeyboard::KeyCode keycode,Event* event);
	void onReleased(EventKeyboard::KeyCode keycode,Event* event);
	//添加子弹
	void addBullet(float dt);
	//添加对子弹的更新事务
	void monitorBullet(float dt);
	//添加返回菜单栏的点击事件
	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchmoved(Touch* touch,Event* event);
	void onTouchend(Touch* touch,Event* event);
	//添加敌机
	void addEnemy(float dt);
	//敌机移动
	void enemyMove(float dt);
	//销毁敌机
	void removeEnemy(float dt);
	//碰撞检测
	void collisionDetect(float dt);
	//移处击中特效精灵
	void removeHitSprite(float dt);
	//分数更新
	void scoreUpdate(float dt);
	//敌军子弹位置更新
	void enemyBulletMove(float dt);
};
#endif // !_PLAY_SCENE_H

