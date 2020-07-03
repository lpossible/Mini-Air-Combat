#ifndef _BOSS_ONE_H
#define _BOSS_ONE_H
#include"cocos2d.h"
#include"Boss.h"
#include"EnemyBulletSprite.h"
#include<math.h>
USING_NS_CC;
class BossOne :public Boss
{
public:
	bool init()override;
	static BossOne* createBossOne(SpriteFrame* spriteFrame);
	virtual void fire()override;
	virtual void move()override;
	virtual void destory()override;
	//��ŭ����
	virtual void firstfire();
	//��ŭ�ƶ�
	virtual void firstMove();
	Vector<EnemyBulletSprite*> BulletVector;
	bool moveflag = false;
	bool fireflag = false;
	int lifenum = 1000;
	bool isalive = true;
private:
	//������ɷ��غ���
	void moveCallback();
	//���𷵻�
	void fireCallback();
	//���𷵻غ���
	void destoryCallback();
};
#endif // !_BOSS_ONE_H

