#ifndef _PLAY_SCENE_H
#define _PLAY_SCENE_H
#include"cocos2d.h"
#include"EnemyBulletSprite.h"
#include<map>
USING_NS_CC;
class PlayScene:public Scene
{
private:
	//��Ӽ��̵��map
	std::map<EventKeyboard::KeyCode, bool> keymap;
	//����ҷ��ɻ��ӵ�vector
	cocos2d::Vector<Sprite*> Bulletvector;
	//��ӵл�Vector
	Vector<Sprite*> Enemyvector;
	//������Ч
	Vector<Sprite*> HitSpriteVector;
	//�л��ӵ�vector
	Vector<EnemyBulletSprite*> EnemyBulletVector;
	//����״̬�л�
	bool flag = true;
	//��ͼƫ��
	int offset = 636;
	//����ͼ
	Sprite* bgSprite;
	//���������¼�
	EventListenerKeyboard* listener;
	//��������
	int score = 0;
	Label* scoreLabel=nullptr;
	//
	SpriteFrame* enemyBulletFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("W2.png");
public:
	bool init()override;
	CREATE_FUNC(PlayScene);
	//��ӶԼ����¼����µ�λ�ø���
	void updatePlanePosition(float dt);
	void updatePlaneStatus(float dt);
	void updateBgStatus(float dt);
	void onKeyPressed(EventKeyboard::KeyCode keycode,Event* event);
	void onReleased(EventKeyboard::KeyCode keycode,Event* event);
	//����ӵ�
	void addBullet(float dt);
	//��Ӷ��ӵ��ĸ�������
	void monitorBullet(float dt);
	//��ӷ��ز˵����ĵ���¼�
	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchmoved(Touch* touch,Event* event);
	void onTouchend(Touch* touch,Event* event);
	//��ӵл�
	void addEnemy(float dt);
	//�л��ƶ�
	void enemyMove(float dt);
	//���ٵл�
	void removeEnemy(float dt);
	//��ײ���
	void collisionDetect(float dt);
	//�ƴ�������Ч����
	void removeHitSprite(float dt);
	//��������
	void scoreUpdate(float dt);
	//�о��ӵ�λ�ø���
	void enemyBulletMove(float dt);
};
#endif // !_PLAY_SCENE_H

