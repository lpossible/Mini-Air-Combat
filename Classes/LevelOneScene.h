#ifndef _LEVEL_ONE_SCENE_H
#define _LEVEL_ONE_SCENE_H
#include"cocos2d.h"
#include"EnemyBulletSprite.h"
#include"BossOne.h"
#include<map>
USING_NS_CC;
class LevelOneScene :public Scene
{
private:
	//添加键盘点击map
	std::map<EventKeyboard::KeyCode, bool> keymap;
	//添加我方飞机子弹vector
	cocos2d::Vector<Sprite*> Bulletvector;
	//击中特效
	Vector<Sprite*> HitSpriteVector;
	//主机状态切换
	bool flag = true;
	//地图偏量
	int offset = 636;
	//背景图
	Sprite* bgSprite;
	//主机触发事件
	EventListenerKeyboard* listener;
	//等级boss
	BossOne* boss;
	//boss位置
	Vec2 bosspoint = Vec2(160,399);
	//boss动作加载完成
	void moveEnable();
	//boss上一个动作执行完成
	void moveCallback();
	//bossFire IS ABLE
	void fireEnable();
	//boss血量绘制
	void bossLife(float dt);
	//击中boss
	void hitBoss(float dt);
	//是否摧毁
	bool isdestory = false;
public:
	bool init()override;
	CREATE_FUNC(LevelOneScene);
	//添加对键盘事件导致的位置更新
	void updatePlanePosition(float dt);
	void updatePlaneStatus(float dt);
	void updateBgStatus(float dt);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onReleased(EventKeyboard::KeyCode keycode, Event* event);
	//添加子弹
	void addBullet(float dt);
	//添加对子弹的更新事务
	void monitorBullet(float dt);
	//添加返回菜单栏的点击事件
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchmoved(Touch* touch, Event* event);
	void onTouchend(Touch* touch, Event* event);
	//移处击中特效精灵
	void removeHitSprite(float dt);
	//添加boss
	void bossArise();
	//添加bosss自动释放子弹
	void bossFire(float dt);
	//boss子弹移动
	void bossBulletMove(float dt);
	//boss子弹击中和出界检测
	void bossBulletDetect(float dt);
	//boss移动
	void bossMove(float dt);
	//BOSS毁灭
	void bossDestory(float dt);
};
#endif // !_LEVEL_ONE_SCENE_H

