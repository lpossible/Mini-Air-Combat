#include"BossOne.h"
#define PI 3.1415926
bool BossOne::init()
{
	if (!Boss::init())
	{
		return false;
	}
	return true;
}

BossOne* BossOne::createBossOne(SpriteFrame* spriteFrame)
{
	BossOne* sprite = new (std::nothrow) BossOne();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void BossOne::fire()
{
	SpriteFrame* spriteframe = SpriteFrameCache::getInstance()->getSpriteFrameByName("W2.png");
	auto const pos = this->getPosition();
	auto const bossSize = this->getContentSize();
	auto const bulletl = EnemyBulletSprite::createEnemyBullet(spriteframe);
	bulletl->speed[0] = 0;
	bulletl->speed[1] = -5;
	auto const bulletr = EnemyBulletSprite::createEnemyBullet(spriteframe);
	bulletr->speed[0] = 0;
	bulletr->speed[1] = -5;
	auto const bulletSize = bulletl->getContentSize();
	bulletl->setPosition(Vec2(pos.x - 10, pos.y - bossSize.height / 2 - bulletSize.height / 2));
	bulletr->setPosition(Vec2(pos.x + 10, pos.y - bossSize.height / 2 - bulletSize.height / 2));
	this->getParent()->addChild(bulletl);
	this->getParent()->addChild(bulletr);
	BulletVector.pushBack(bulletl);
	BulletVector.pushBack(bulletr);
}
void BossOne::move()
{
	const auto pos = this->getPosition();
	const int direction = random() % 10;
	const auto winsize = Director::getInstance()->getWinSize();
	const auto contentsize = this->getContentSize();
	if (direction == 0)
	{
		const Vec2 point = Vec2(pos.x, pos.y + 80);
		const auto moveby = MoveTo::create(0.5f, point);
		const auto seq = Sequence::create(moveby, CallFunc::create(CC_CALLBACK_0(BossOne::moveCallback, this)), NULL);
		if (point.y - contentsize.height / 2 < winsize.height)
		{
			moveflag = false;
			this->runAction(seq);
		}
	}
	else if (direction == 1)
	{
		const Vec2 point = Vec2(pos.x, pos.y - 80);
		const auto moveby = MoveTo::create(0.5f, point);
		const auto seq = Sequence::create(moveby, CallFunc::create(CC_CALLBACK_0(BossOne::moveCallback, this)), NULL);
		if (point.y - contentsize.height / 2 > winsize.height / 2)
		{
			moveflag = false;
			this->runAction(seq);
		}
	}
	else if (direction == 2)
	{
		const Vec2 point = Vec2(pos.x - 40, pos.y);
		const auto moveby = MoveTo::create(0.5f, point);
		const auto seq = Sequence::create(moveby, CallFunc::create(CC_CALLBACK_0(BossOne::moveCallback, this)), NULL);
		if (point.x - contentsize.width / 2 > 0)
		{
			moveflag = false;
			this->runAction(seq);
		}
	}
	else if (direction == 3)
	{
		const Vec2 point = Vec2(pos.x + 40, pos.y);
		const auto moveby = MoveTo::create(0.5f, point);
		const auto seq = Sequence::create(moveby, CallFunc::create(CC_CALLBACK_0(BossOne::moveCallback, this)), NULL);
		if (point.x + contentsize.width / 2 < winsize.width)
		{
			moveflag = false;
			this->runAction(seq);
		}
	}
	else
	{

	}
}

void BossOne::destory()
{
	const auto animation = AnimationCache::getInstance()->getAnimation("explosion");
	auto const animate = Animate::create(animation);
	auto const seq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(BossOne::destoryCallback, this)), NULL);
	this->runAction(seq);
}

void BossOne::firstfire()
{
	SpriteFrame* spriteframe = SpriteFrameCache::getInstance()->getSpriteFrameByName("W2.png");
	int bulletnum = 8;
	auto const pos = this->getPosition();
	auto const bossSize = this->getContentSize();
	auto const midbullet = EnemyBulletSprite::createEnemyBullet(spriteframe);
	const auto bulletSize = midbullet->getContentSize();
	const auto r = bossSize.height / 2 + bulletSize.height / 2;
	midbullet->setPosition(Vec2(pos.x, pos.y-r));
	midbullet->speed[0] = 0;
	midbullet->speed[1] = -5;
	BulletVector.pushBack(midbullet);
    const float offset = 12;
	this->getParent()->addChild(midbullet);
	for (int i = 1; i <= bulletnum; ++i)
	{
		if (i <= 4)
		{
			auto const bullet = EnemyBulletSprite::createEnemyBullet(spriteframe);
			const float angle = (offset * i) * PI / 180.0f;
			bullet->setPosition(Vec2(pos.x - r*sin(angle), pos.y - r*cos(angle)));
			bullet->speed[1] = -5;
			bullet->speed[0] = -5*tan(angle);
			this->getParent()->addChild(bullet);
			BulletVector.pushBack(bullet);
		}
		else
		{
			auto const bullet = EnemyBulletSprite::createEnemyBullet(spriteframe);
			const float angle = (offset * (i-4)) * PI / 180.0f;
			bullet->setPosition(Vec2(pos.x + r * sin(angle), pos.y - r * cos(angle)));
			bullet->speed[1] = -5;
			bullet->speed[0] = 5*tan(angle);
			this->getParent()->addChild(bullet);
			BulletVector.pushBack(bullet);
		}
	}
}

void BossOne::firstMove()
{
	const auto pos = this->getParent()->getChildByTag(1)->getPosition();
	//闪烁
	//const auto const blink = Blink::create(1, 0.1f);
	//消失
	const auto const fadeout = FadeOut::create(0.5f);
	//移动
	const auto const movebto = MoveTo::create(0.2f, Vec2(pos.x, pos.y + 150));
	//出现
	const auto const fadein = FadeIn::create(0.5f);
	//阶段二,移动到源点
	const auto const smoveto = MoveTo::create(3.0f, Vec2(160, 399));
	//动作序列
	const auto const seq = Sequence::create(fadeout, movebto, fadein, CallFunc::create(CC_CALLBACK_0(BossOne::fireCallback, this)), smoveto, CallFunc::create(CC_CALLBACK_0(BossOne::moveCallback, this)), NULL);
	moveflag = false;
	fireflag = false;
	this->runAction(seq);
}

void BossOne::moveCallback()
{
	moveflag = true;
}

void BossOne::fireCallback()
{
	fireflag = true;
}

void BossOne::destoryCallback()
{
	isalive = false;
}
