#include"LevelOneScene.h"
#include"AudioEngine.h"
using namespace experimental;
bool LevelOneScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto const size = Director::getInstance()->getWinSize();
	bgSprite = Sprite::createWithSpriteFrameName("bg01.png");
	bgSprite->setTextureRect(Rect(2, offset, 480, 533));
	bgSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	bgSprite->setContentSize(size);
	addChild(bgSprite);
	//添加飞机
	auto const unfireSprite = Sprite::createWithSpriteFrameName("ship02.png");
	unfireSprite->setAnchorPoint(Vec2(0.5, 0));
	unfireSprite->setPosition(Vec2(size.width / 2, 0));
	unfireSprite->setTag(1);
	unfireSprite->setScale(0.5f);
	addChild(unfireSprite);
	//添加Boss
	bossArise();
	//绘制血量框
	Vec2 point[4];
	point[0] = Vec2(10,523);
	point[1] = Vec2(310,523);
	point[2] = Vec2(310,507);
	point[3] = Vec2(10,507);
	//drawNode
	DrawNode* drawnode = DrawNode::create();
	drawnode->drawPolygon(point,4,Color4F::BLACK,1,Color4F::GRAY);
	addChild(drawnode);
	// 添加返回主菜单label
	auto const backLabel = Label::createWithTTF("Menu", "fonts/arial.ttf", 20);
	backLabel->setColor(Color3B::WHITE);
	backLabel->enableOutline(Color4B::RED, 5);
	backLabel->setPosition(Vec2(size.width - backLabel->getContentSize().width / 2, backLabel->getContentSize().height / 2 + 5));
	//添加backLabel的点击事件
	auto backLabellistener = EventListenerTouchOneByOne::create();
	backLabellistener->onTouchBegan = CC_CALLBACK_2(LevelOneScene::onTouchBegan, this);
	backLabellistener->onTouchMoved = CC_CALLBACK_2(LevelOneScene::onTouchmoved, this);
	backLabellistener->onTouchEnded = CC_CALLBACK_2(LevelOneScene::onTouchend, this);
	addChild(backLabel);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backLabellistener, backLabel);
	//添加键盘事件
	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(LevelOneScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(LevelOneScene::onReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, unfireSprite);
	//每一帧改变飞机的射击状态
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::updatePlaneStatus));
	//检测键盘输入对飞机做出相应的移动
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::updatePlanePosition));
	//添加子弹
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::addBullet), 0.08);
	//移动背景
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::updateBgStatus));
	//检测子弹状态
	//boss毁灭
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::bossDestory));
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::monitorBullet));
	//移除特效精灵
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::removeHitSprite), 0.2);
	//boss攻击
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::bossFire), 0.5f);
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::bossBulletDetect));
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::bossBulletMove));
	//boss移动
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::bossMove),0.5f);
	//击中boss
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::hitBoss));
	//绘制boss血量
	schedule(CC_SCHEDULE_SELECTOR(LevelOneScene::bossLife));
	return true;
}
void LevelOneScene::updatePlaneStatus(float dt)
{
	flag = !flag;
	const auto pos = this->getChildByTag(1)->getPosition();
	this->removeChildByTag(1);
	if (flag)
	{
		auto const unfireSprite = Sprite::createWithSpriteFrameName("ship02.png");
		unfireSprite->setPosition(pos.x, pos.y);
		unfireSprite->setAnchorPoint(Vec2(0.5, 0));
		unfireSprite->setTag(1);
		unfireSprite->setScale(0.5f);
		addChild(unfireSprite);
		listener = EventListenerKeyboard::create();
		listener->onKeyPressed = CC_CALLBACK_2(LevelOneScene::onKeyPressed, this);
		listener->onKeyReleased = CC_CALLBACK_2(LevelOneScene::onReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, unfireSprite);
	}
	else
	{
		auto const fireSprite = Sprite::createWithSpriteFrameName("ship01.png");
		fireSprite->setPosition(pos.x, pos.y);
		fireSprite->setTag(1);
		fireSprite->setAnchorPoint(Vec2(0.5, 0));
		fireSprite->setScale(0.5f);
		addChild(fireSprite);
		listener = EventListenerKeyboard::create();
		listener->onKeyPressed = CC_CALLBACK_2(LevelOneScene::onKeyPressed, this);
		listener->onKeyReleased = CC_CALLBACK_2(LevelOneScene::onReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, fireSprite);
	}
}
void LevelOneScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	keymap[keycode] = true;
}
void LevelOneScene::onReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	keymap[keycode] = false;
}
void LevelOneScene::updatePlanePosition(float dt)
{
	const auto up = EventKeyboard::KeyCode::KEY_W;
	const auto left = EventKeyboard::KeyCode::KEY_A;
	const auto down = EventKeyboard::KeyCode::KEY_S;
	const auto right = EventKeyboard::KeyCode::KEY_D;
	const auto hit = EventKeyboard::KeyCode::KEY_J;
	const auto pos = this->getChildByTag(1)->getPosition();
	const auto size = Director::getInstance()->getWinSize();
	const auto const planeSprite = this->getChildByTag(1);
	if (keymap[up])
	{
		if (planeSprite->getPositionY() + planeSprite->getContentSize().height + 5 <= size.height)
		{
			planeSprite->setPosition(pos.x, pos.y + 5);
		}
		else
		{
			planeSprite->setPosition(pos.x, size.height - planeSprite->getContentSize().height);
		}
	}
	if (keymap[left])
	{
		if (planeSprite->getPositionX() - 5 >= planeSprite->getContentSize().width / 2)
		{
			planeSprite->setPosition(pos.x - 5, pos.y);
		}
		else
		{
			planeSprite->setPosition(planeSprite->getContentSize().width / 2, pos.y);
		}
	}
	if (keymap[down])
	{
		if (planeSprite->getPositionY() - 5 >= 0)
		{
			planeSprite->setPosition(pos.x, pos.y - 5);
		}
		else
		{
			planeSprite->setPosition(pos.x, 0);
		}
	}
	if (keymap[right])
	{
		if (planeSprite->getPositionX() + planeSprite->getContentSize().width / 2 + 5 <= size.width)
		{
			planeSprite->setPosition(pos.x + 5, pos.y);
		}
		else
		{
			planeSprite->setPosition(size.width - planeSprite->getContentSize().width / 2, pos.y);
		}
	}
}
void LevelOneScene::addBullet(float dt)
{
	const auto hit = EventKeyboard::KeyCode::KEY_J;
	const auto pos = this->getChildByTag(1)->getPosition();
	const auto const planeSprite = this->getChildByTag(1);
	if (keymap[hit])
	{
		auto const bulletl = Sprite::createWithSpriteFrameName("W1.png");
		auto const selfszie = bulletl->getContentSize();
		auto const bulletr = Sprite::createWithSpriteFrameName("W1.png");
		Bulletvector.pushBack(bulletl);
		Bulletvector.pushBack(bulletr);
		auto const contentsize = planeSprite->getContentSize();
		bulletl->setPosition(Vec2(pos.x - 10, pos.y + contentsize.height + selfszie.height / 2));
		bulletr->setPosition(Vec2(pos.x + 10, pos.y + contentsize.height + selfszie.height / 2));
		bulletl->setScale(0.5f);
		bulletr->setScale(0.5f);
		AudioEngine::play2d("Music/fireEffect.mp3", false, 0.1);
		addChild(bulletl);
		addChild(bulletr);
	}
}
void LevelOneScene::updateBgStatus(float dt)
{
	offset -= 1;
	if (offset < 2)
	{
		offset = 636;
	}
	bgSprite->setTextureRect(Rect(2, offset, 480, 533));
}
void LevelOneScene::monitorBullet(float dt)
{
	if (!Bulletvector.empty())
	{
		Vector<Sprite*> removeBullet;
		for (auto  each_bullet = Bulletvector.begin(); each_bullet != Bulletvector.end(); ++each_bullet)
		{
			auto const old_position = (*each_bullet)->getPosition();
			auto const new_pos_y = old_position.y + 10;
			if (new_pos_y >= 533)
			{
				removeBullet.pushBack(*each_bullet);
			}
			else
			{
				(*each_bullet)->setPosition(Vec2(old_position.x, new_pos_y));
			}
		}
		for (auto bullet = removeBullet.begin(); bullet != removeBullet.end(); bullet++)
		{
			Bulletvector.eraseObject(*bullet);
			this->removeChild(*bullet);
		}
	}
}
bool LevelOneScene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void LevelOneScene::onTouchend(Touch* touch, Event* event)
{
	const auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
	auto const pos = sprite->convertTouchToNodeSpace(touch);
	auto const rect = Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height);
	if (rect.containsPoint(pos))
	{
		AudioEngine::stopAll();
		AudioEngine::play2d("Music/mainMainMusic.mp3", true, 0.2);
		Director::getInstance()->popScene();
	}
}
void LevelOneScene::onTouchmoved(Touch* touch, Event* event)
{

}
void LevelOneScene::removeHitSprite(float dt)
{
	if (!HitSpriteVector.empty())
	{
		for (auto const hit_sptrite : HitSpriteVector)
		{
			this->removeChild(hit_sptrite);
		}
		HitSpriteVector.clear();
	}
}

void LevelOneScene::bossArise()
{
	auto bossframe = SpriteFrameCache::getInstance()->getSpriteFrameByName("E5.png");
	boss = BossOne::createBossOne(bossframe);
	boss->setPosition(Vec2(160,633));
	boss->setRotation(180);
	addChild(boss);
	const auto blink = Blink::create(2.0f,5);
	const auto moveto = MoveTo::create(2.0f, bosspoint);
	const auto spawn = Spawn::create(blink, moveto, NULL);
	const auto seq = Sequence::create(spawn, CallFunc::create(CC_CALLBACK_0(LevelOneScene::moveEnable, this)), CallFunc::create(CC_CALLBACK_0(LevelOneScene::fireEnable, this)), NULL);
	boss->runAction(seq);
}

void LevelOneScene::bossFire(float dt)
{
	if (boss!=nullptr)
	{
		if (boss->fireflag)
		{
			if (boss->lifenum >= 800)
			{
				boss->fire();
			}
			else
			{
				boss->firstfire();
			}
		}
	}
}

void LevelOneScene::bossBulletMove(float dt)
{
	if (boss!=nullptr)
	{
		if (!boss->BulletVector.empty())
		{
			for (auto const bullet : boss->BulletVector)
			{
				bullet->move();
			}
		}
	}
}

void LevelOneScene::bossBulletDetect(float dt)
{
	if (boss!=nullptr)
	{
		Vector<EnemyBulletSprite*> removeBullet;
		for (auto const bullet : boss->BulletVector)
		{
			if (bullet->getPositionY() + bullet->getContentSize().height / 2 < 0)
			{
				removeBullet.pushBack(bullet);
			}
		}
		if (!removeBullet.empty())
		{
			for (auto const bullet : removeBullet)
			{
				boss->BulletVector.eraseObject(bullet);
			}
		}
	}
}
void LevelOneScene::bossMove(float dt)
{
	const int moveStatus = random() % 20;
	if (boss!=nullptr)
	{
		if (boss->moveflag)
		{
			if (boss->lifenum > 600)
			{
				boss->move();
			}
			else
			{
				if (moveStatus <= 18)
				{
					boss->move();
				}
				else
				{
					boss->firstMove();
				}
			}
		}
	}
}
void LevelOneScene::bossDestory(float dt)
{
	if (boss!=nullptr&&!isdestory)
	{
		if (boss->lifenum <= 0)
		{
			boss->moveflag = false;
			boss->fireflag = false;
			for (auto bullet : boss->BulletVector)
			{
				this->removeChild(bullet);
			}
			boss->BulletVector.clear();
			boss->destory();
			isdestory = true;
			boss->isalive = false;
		}
	}
	if (boss!=nullptr&&!boss->isalive)
	{
		this->removeChild(boss);
	}
}
void LevelOneScene::moveEnable()
{
	if (boss != nullptr)
	{
		boss->moveflag = true;
	}
}
void LevelOneScene::moveCallback()
{
	if (boss != nullptr)
	{
		boss->moveflag = true;
	}
}

void LevelOneScene::fireEnable()
{
	if (boss != nullptr)
	{
		boss->fireflag = true;
	}
}

void LevelOneScene::bossLife(float dt)
{
	if (boss != nullptr)
	{
		Vec2 point[4];
		auto des = boss->lifenum / 1000.0 * 300;
		auto pos = 10 + des;
		point[0] = Vec2(10, 522);
		point[1] = Vec2(pos, 522);
		point[2] = Vec2(pos, 508);
		point[3] = Vec2(10, 508);
		auto color = Color4F();
		if (boss->lifenum >= 800)
		{
			color = Color4F::BLUE;
		}
		else if (boss->lifenum >= 600)
		{
			color = Color4F::GREEN;
		}
		else if (boss->lifenum >= 400)
		{
			color = Color4F::YELLOW;
		}
		else
		{
			color = Color4F::RED;
		}
		auto drawnode = this->getChildByName("drawnode");
		if (drawnode == nullptr)
		{
			auto const drawnode = DrawNode::create();
			drawnode->drawPolygon(point, 4, color, 1, Color4F(1, 0, 0, 0));
			drawnode->setName("drawnode");
			addChild(drawnode);
		}
		else
		{
			this->removeChild(drawnode);
			auto const drawnode = DrawNode::create();
			drawnode->drawPolygon(point, 4, color, 1, Color4F(1, 0, 0, 0));
			drawnode->setName("drawnode");
			addChild(drawnode);
		}
	}
}

void LevelOneScene::hitBoss(float dt)
{
	if (boss != nullptr&&!isdestory)
	{
		Vector<Sprite*> removeBullet;
		for (auto const bullet : Bulletvector)
		{
			if (bullet->getBoundingBox().intersectsRect(boss->getBoundingBox()))
			{
				const auto pos = bullet->getPosition();
				const auto hit = Sprite::createWithSpriteFrameName("hit.png");
				hit->setPosition(pos.x, boss->getPositionY());
				addChild(hit);
				AudioEngine::play2d("Music/fireEffect.mp3", false, 0.1f);
				removeBullet.pushBack(bullet);
				HitSpriteVector.pushBack(hit);
				boss->lifenum -= 1;
			}
		}
		for (auto bullet : removeBullet)
		{
			Bulletvector.eraseObject(bullet);
			this->removeChild(bullet);
		}
		removeBullet.clear();
	}
}
