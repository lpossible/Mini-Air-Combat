#include"PlayScene.h"
#include"AudioEngine.h"
using namespace experimental;
bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	bgSprite = Sprite::createWithSpriteFrameName("bg01.png");
	bgSprite->setTextureRect(Rect(2, offset, 480, 533));
	bgSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	bgSprite->setContentSize(size);
	addChild(bgSprite);
	//添加飞机
	auto unfireSprite = Sprite::createWithSpriteFrameName("ship02.png");
	unfireSprite->setAnchorPoint(Vec2(0.5, 0));
	unfireSprite->setPosition(Vec2(size.width / 2, 0));
	unfireSprite->setTag(1);
	addChild(unfireSprite);
	//添加生命显示飞机
	const auto lifeSprite = Sprite::createWithSpriteFrameName("ship03.png");
	const auto lifeSize = Size(50, 50);
	lifeSprite->setContentSize(lifeSize);
	lifeSprite->setPosition(Vec2(lifeSize.width / 2, size.height - lifeSize.height / 2));
	addChild(lifeSprite);
	//显示当前分数
	scoreLabel = Label::createWithBMFont("fonts/arial-14.fnt", std::to_string(score));
	scoreLabel->setPosition(Vec2(size.width-scoreLabel->getContentSize().width-10,size.height-scoreLabel->getContentSize().height/2));
	addChild(scoreLabel);
	//添加生命值显示
	const auto lifeNum = Label::createWithBMFont("fonts/arial-14.fnt", "2");
	lifeNum->setPosition(Vec2(lifeSprite->getPositionX() + 25 + lifeNum->getContentSize().width / 2 + 10, lifeSprite->getPositionY() - 6));
	addChild(lifeNum);
	// 添加返回主菜单label
	auto backLabel = Label::createWithTTF("Menu", "fonts/arial.ttf", 20);
	backLabel->setColor(Color3B::WHITE);
	backLabel->enableOutline(Color4B::RED, 5);
	backLabel->setPosition(Vec2(size.width - backLabel->getContentSize().width / 2, backLabel->getContentSize().height / 2+5));
	//添加backLabel的点击事件
	auto backLabellistener = EventListenerTouchOneByOne::create();
	backLabellistener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	backLabellistener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchmoved, this);
	backLabellistener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchend, this);
	addChild(backLabel);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backLabellistener, backLabel);
	//添加键盘事件
	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, unfireSprite);
	//每一帧绘制分数
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::scoreUpdate));
	//每一帧改变飞机的射击状态
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::updatePlaneStatus));
	//检测键盘输入对飞机做出相应的移动
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::updatePlanePosition));
	//添加子弹
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::addBullet),0.08);
	//移动背景
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::updateBgStatus));
	//检测子弹状态
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::monitorBullet));
	//添加敌机
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::addEnemy), 1);
	//移动敌机
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::enemyMove));
	//移出敌机
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::removeEnemy));
	//碰撞检测
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::collisionDetect));
	//移除特效精灵
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::removeHitSprite), 0.2);
	//测试子弹移动
	auto enemyBullet = EnemyBulletSprite::createEnemyBullet(enemyBulletFrame);
	enemyBullet->setPosition(Vec2(size.width/2,size.height/2));
	enemyBullet->speed[0] = 1;
	enemyBullet->speed[1] = 2;
	addChild(enemyBullet);
	EnemyBulletVector.pushBack(enemyBullet);
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::enemyBulletMove),1);
	return true;
}
void PlayScene::updatePlaneStatus(float dt)
{
	flag = !flag;
	const auto pos = this->getChildByTag(1)->getPosition();
	this->removeChildByTag(1);
	if (flag)
	{
		auto unfireSprite = Sprite::createWithSpriteFrameName("ship02.png");
		unfireSprite->setPosition(pos.x, pos.y);
		unfireSprite->setAnchorPoint(Vec2(0.5, 0));
		unfireSprite->setTag(1);
		addChild(unfireSprite);
		listener = EventListenerKeyboard::create();
		listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
		listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, unfireSprite);
	}
	else
	{
		auto fireSprite = Sprite::createWithSpriteFrameName("ship01.png");
		fireSprite->setPosition(pos.x, pos.y);
		fireSprite->setTag(1);
		fireSprite->setAnchorPoint(Vec2(0.5, 0));
		addChild(fireSprite);
		listener = EventListenerKeyboard::create();
		listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
		listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, fireSprite);
	}
}
void PlayScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	keymap[keycode] = true;
}
void PlayScene::onReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	keymap[keycode] = false;
}
void PlayScene::updatePlanePosition(float dt)
{
	const auto up = EventKeyboard::KeyCode::KEY_W;
	const auto left = EventKeyboard::KeyCode::KEY_A;
	const auto down = EventKeyboard::KeyCode::KEY_S;
	const auto right = EventKeyboard::KeyCode::KEY_D;
	const auto hit = EventKeyboard::KeyCode::KEY_J;
	const auto pos = this->getChildByTag(1)->getPosition();
	const auto size = Director::getInstance()->getWinSize();
	auto planeSprite = this->getChildByTag(1);
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
void PlayScene::addBullet(float dt)
{
	const auto hit = EventKeyboard::KeyCode::KEY_J;
	const auto pos = this->getChildByTag(1)->getPosition();
	auto planeSprite = this->getChildByTag(1);
	if (keymap[hit])
	{
		auto bulletl = Sprite::createWithSpriteFrameName("W1.png");
		auto selfszie = bulletl->getContentSize();
		auto bulletr = Sprite::createWithSpriteFrameName("W1.png");
		Bulletvector.pushBack(bulletl);
		Bulletvector.pushBack(bulletr);
		auto contentsize = planeSprite->getContentSize();
		bulletl->setPosition(Vec2(pos.x - 10, pos.y + contentsize.height + selfszie.height / 2));
		bulletr->setPosition(Vec2(pos.x + 10, pos.y + contentsize.height + selfszie.height / 2));
		AudioEngine::play2d("Music/fireEffect.mp3", false, 0.1);
		addChild(bulletl);
		addChild(bulletr);
	}
}
void PlayScene::updateBgStatus(float dt)
{
	offset -= 1;
	if (offset < 2)
	{
		offset = 636;
	}
	bgSprite->setTextureRect(Rect(2, offset, 480, 533));
}
void PlayScene::monitorBullet(float dt)
{
	if (Bulletvector.size() != 0)
	{
		cocos2d::Vector<Sprite*> removeBullet;
		for (auto each_bullet = Bulletvector.begin(); each_bullet != Bulletvector.end(); each_bullet++)
		{
			auto old_position = (*each_bullet)->getPosition();
			auto new_pos_y = old_position.y + 10;
			if (new_pos_y >= 533)
			{
				removeBullet.pushBack((*each_bullet));
			}
			else
			{
				(*each_bullet)->setPosition(Vec2(old_position.x, new_pos_y));
			}
		}
		for (auto bullet = removeBullet.begin(); bullet != removeBullet.end(); bullet++)
		{
			Bulletvector.eraseObject((*bullet));
			this->removeChild((*bullet));
		}
	}
}
bool PlayScene::onTouchBegan(Touch* touch,Event* event)
{
	return true;
}
void PlayScene::onTouchend(Touch* touch, Event* event)
{
	auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
	auto pos = sprite->convertTouchToNodeSpace(touch);
	auto rect = Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height);
	if (rect.containsPoint(pos))
	{
		AudioEngine::stopAll();
		AudioEngine::play2d("Music/mainMainMusic.mp3", true, 0.2);
		Director::getInstance()->popScene();
	}
}
void PlayScene::onTouchmoved(Touch* touch, Event* event)
{
	
}
void PlayScene::addEnemy(float dt)
{
	const int x = random() % 220 + 50;
	const int y = random() % 450 + 550;
	auto enemy = Sprite::createWithSpriteFrameName("E5.png");
	enemy->setRotation(180);
	enemy->setScale(0.6f);
	enemy->setPosition(Vec2(x,y));
	addChild(enemy);
	Enemyvector.pushBack(enemy);
}
void PlayScene::removeEnemy(float dt)
{
    Vector<Sprite*> removeVector;
	if (!Enemyvector.empty())
	{
		for (auto enemy = Enemyvector.begin(); enemy != Enemyvector.end(); enemy++)
		{
			if ((*enemy)->getPositionY() < 51)
			{
				removeVector.pushBack((*enemy));
				removeChild((*enemy));
			}
		}
		for (auto enemy : removeVector)
		{
			Enemyvector.eraseObject(enemy);
		}
	}
}
void PlayScene::enemyMove(float dt)
{
	if (!Enemyvector.empty())
	{
		for (auto enemy = Enemyvector.begin(); enemy != Enemyvector.end(); enemy++)
		{
			(*enemy)->setPosition(Vec2((*enemy)->getPositionX(),(*enemy)->getPositionY()-2));
		}
	
	}
}
void PlayScene::scoreUpdate(float dt)
{
	if (scoreLabel)
	{
		scoreLabel->setString(std::to_string(score));
	}
}
void PlayScene::enemyBulletMove(float dt)
{
	if (!EnemyBulletVector.empty())
	{
		for (auto const& each : EnemyBulletVector)
		{
			each->move();
		}
	}
}
void PlayScene::collisionDetect(float dt)
{
	Vector<Sprite*> hitSprite;
	Vector<Sprite*> hitbulletSprite;
	for (auto const &each_bullet : Bulletvector)
	{
		for (auto const &each_enemy : Enemyvector)
		{
			if (each_bullet->getBoundingBox().intersectsRect(each_enemy->getBoundingBox()))
			{
				score += 10;
				AudioEngine::play2d("Music/explodeEffect.mp3",false,0.2);
				auto pos = each_enemy->getPosition();
				//击中精灵
				auto hit_effect = Sprite::createWithSpriteFrameName("hit.png");
				hit_effect->setPosition(pos);
				this->removeChild(each_enemy);
				this->removeChild(each_bullet);
				addChild(hit_effect);
				HitSpriteVector.pushBack(hit_effect);
				hitSprite.pushBack(each_enemy);
				hitbulletSprite.pushBack(each_bullet);

			}
		}
	}
	for (auto const &hit_enemy : hitSprite)
	{
		Enemyvector.eraseObject(hit_enemy);
	}
	for (auto const& hit_bullet : hitbulletSprite)
	{
		Bulletvector.eraseObject(hit_bullet);
	}
}
void PlayScene::removeHitSprite(float dt)
{
	if (!HitSpriteVector.empty())
	{
		for (auto const &hit_sptrite : HitSpriteVector)
		{
			this->removeChild(hit_sptrite);
		}
		HitSpriteVector.clear();
	}
}