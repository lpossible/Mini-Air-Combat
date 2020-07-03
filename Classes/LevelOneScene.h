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
	//��Ӽ��̵��map
	std::map<EventKeyboard::KeyCode, bool> keymap;
	//����ҷ��ɻ��ӵ�vector
	cocos2d::Vector<Sprite*> Bulletvector;
	//������Ч
	Vector<Sprite*> HitSpriteVector;
	//����״̬�л�
	bool flag = true;
	//��ͼƫ��
	int offset = 636;
	//����ͼ
	Sprite* bgSprite;
	//���������¼�
	EventListenerKeyboard* listener;
	//�ȼ�boss
	BossOne* boss;
	//bossλ��
	Vec2 bosspoint = Vec2(160,399);
	//boss�����������
	void moveEnable();
	//boss��һ������ִ�����
	void moveCallback();
	//bossFire IS ABLE
	void fireEnable();
	//bossѪ������
	void bossLife(float dt);
	//����boss
	void hitBoss(float dt);
	//�Ƿ�ݻ�
	bool isdestory = false;
public:
	bool init()override;
	CREATE_FUNC(LevelOneScene);
	//��ӶԼ����¼����µ�λ�ø���
	void updatePlanePosition(float dt);
	void updatePlaneStatus(float dt);
	void updateBgStatus(float dt);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onReleased(EventKeyboard::KeyCode keycode, Event* event);
	//����ӵ�
	void addBullet(float dt);
	//��Ӷ��ӵ��ĸ�������
	void monitorBullet(float dt);
	//��ӷ��ز˵����ĵ���¼�
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchmoved(Touch* touch, Event* event);
	void onTouchend(Touch* touch, Event* event);
	//�ƴ�������Ч����
	void removeHitSprite(float dt);
	//���boss
	void bossArise();
	//���bosss�Զ��ͷ��ӵ�
	void bossFire(float dt);
	//boss�ӵ��ƶ�
	void bossBulletMove(float dt);
	//boss�ӵ����кͳ�����
	void bossBulletDetect(float dt);
	//boss�ƶ�
	void bossMove(float dt);
	//BOSS����
	void bossDestory(float dt);
};
#endif // !_LEVEL_ONE_SCENE_H

