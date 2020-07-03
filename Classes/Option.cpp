#include"Option.h"

Scene* OptionScene::createScene()
{
	return OptionScene::create();
}
bool OptionScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	auto bgSprite = Sprite::create("loading.png");
	bgSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bgSprite, -1);
	auto optionSprite = Sprite::create("menuTitle.png", Rect(0, 0, 134, 39));
	optionSprite->setPosition(Vec2(size.width / 2, 403));
	addChild(optionSprite);
	auto soundLabel = Label::createWithTTF("Sound", "fonts/arial.ttf",20);
	soundLabel->setPosition(Vec2(optionSprite->getPositionX()-100,optionSprite->getPositionY()-50));
	soundLabel->enableGlow(Color4B::BLUE);
	addChild(soundLabel);
	auto modeLabel = Label::createWithTTF("Mode","fonts/arial.ttf",20);
	modeLabel->setPosition(Vec2(optionSprite->getPositionX() + 100, optionSprite->getPositionY() - 50));
	modeLabel->enableGlow(Color4B::BLUE);
	addChild(modeLabel);
	auto backLabel = Label::createWithTTF("Go Back", "fonts/arial.ttf", 20);
	backLabel->setPosition(Vec2(optionSprite->getPositionX(),optionSprite->getPositionY()-150));
	backLabel->setColor(Color3B::WHITE);
	backLabel->enableOutline(Color4B::RED, 3);
	addChild(backLabel);
	vec = backLabel->getPosition();
	//ÉèÖÃ³¡¾°·µ»Ø¼àÌýÆ÷
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(OptionScene::backLabelTouched,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,backLabel);
	return true;
}
bool OptionScene::backLabelTouched(Touch* touch,Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	auto pos = target->convertTouchToNodeSpace(touch);
	auto size = target->getContentSize();
	auto rect = Rect(0,0,size.width,size.height);
	if (rect.containsPoint(pos))
	{
		Director::getInstance()->popScene();
	}
	return true;
}