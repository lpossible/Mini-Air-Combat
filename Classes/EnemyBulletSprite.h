#ifndef _EnemyBulletSprite_H
#define _EnemyBulletSprite_H
#include"cocos2d.h"
USING_NS_CC;
class EnemyBulletSprite:public Sprite
{
public:
	int speed[2];
	bool init()override;
	static EnemyBulletSprite* createEnemyBullet(SpriteFrame* spriteFrame);
	void move();
};
#endif // !_EnemyBulletSprite_H
