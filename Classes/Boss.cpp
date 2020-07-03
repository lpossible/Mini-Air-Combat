#include"Boss.h"

bool Boss::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}
