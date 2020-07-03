#include"About.h"

bool AboutScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	auto bgSprite = Sprite::create("loading.png");
	bgSprite->setPosition(size.width / 2, size.height / 2);
	addChild(bgSprite);
	//添加about标题精灵
	auto titleSprite = Sprite::create("menuTitle.png",Rect(0,40,134,39));
	titleSprite->setPosition(size.width/2,403);
	addChild(titleSprite);
	//添加about内容
	std::string content = "Make sure you know the rules!!\n        Just figt for joy";
	auto contentLabel = Label::createWithTTF(content, "fonts/arial.ttf", 20);
	contentLabel->setPosition(Vec2(titleSprite->getPositionX(), titleSprite->getPositionY() - 120));
	contentLabel->setColor(Color3B::RED);
	contentLabel->enableGlow(Color4B::BLUE);
	addChild(contentLabel);
	//添加游戏信息
    //添加rule标签
	std::string info = "Game Design:Luo Ping\nGame Music:Luo Ping\nGame Special Effect:Luo Ping";
	auto infoLabel = Label::createWithTTF(info, "fonts/arial.ttf", 20);
	infoLabel->setColor(Color3B::ORANGE);
	infoLabel->enableGlow(Color4B::GREEN);
	infoLabel->setPosition(Vec2(titleSprite->getPositionX(), titleSprite->getPositionY() - 250));
	addChild(infoLabel);
	//添加返回标签
	auto backLabel = Label::createWithTTF("Go Back", "fonts/arial.ttf", 20);
	backLabel->setPosition(Vec2(titleSprite->getPositionX(), titleSprite->getPositionY() - 300));
	backLabel->setColor(Color3B::WHITE);
	backLabel->enableOutline(Color4B::RED,3);
	addChild(backLabel);
	//添加点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(AboutScene::backLabelTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, backLabel);
	return true;
}
bool AboutScene::backLabelTouched(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	auto pos = target->convertTouchToNodeSpace(touch);
	auto size = target->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(pos))
	{
		Director::getInstance()->popScene();
	}
	return true;
}