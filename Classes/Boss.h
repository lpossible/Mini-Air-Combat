#ifndef _BOSS_H
#define _BOSS_H
#include"cocos2d.h"
USING_NS_CC;
class Boss :public Sprite
{
private:
	int life = 0;
public:
	int widht = 320;
	int height = 533;
	bool init()override;
	virtual void  fire()=0;
	virtual void  move()=0;
	virtual void  destory()=0;
};
#endif // !_BOSS_H

