#include"MainScene.h"
Scene* MainScene::createScene()
{
	return MainScene::create();
}
bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	const auto size = Director::getInstance()->getWinSize();
	//±³¾°¾«Áé
	auto bgSprite = Sprite::create("loading.png");
	bgSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bgSprite, -1);
	//logo¾«Áé
	auto logoSprite = Sprite::create("logo.png");
	logoSprite->setPosition(Vec2(size.width / 2, 423));
	addChild(logoSprite);
	//´´½¨²Ëµ¥²ã
	auto newgameItem = MenuItemSprite::create(Sprite::create("menu.png", Rect(0, 0, 124, 38)), Sprite::create("menu.png", Rect(0, 38, 124, 38)), Sprite::create("menu.png", Rect(0, 76, 124, 38)), CC_CALLBACK_1(MainScene::menuNewCallback, this));
	auto optionItem = MenuItemSprite::create(Sprite::create("menu.png", Rect(124, 0, 124, 38)), Sprite::create("menu.png", Rect(124, 38, 124, 38)), Sprite::create("menu.png", Rect(124, 76, 124, 38)), CC_CALLBACK_1(MainScene::menuOptionCallback, this));
	auto aboutItem = MenuItemSprite::create(Sprite::create("menu.png", Rect(248, 0, 124, 38)), Sprite::create("menu.png", Rect(248, 38, 124, 38)), Sprite::create("menu.png", Rect(248, 76, 124, 38)), CC_CALLBACK_1(MainScene::menuAboutCallback, this));
	optionItem->setPosition(Vec2(newgameItem->getPositionX(), newgameItem->getPositionY() - 48));
	aboutItem->setPosition(Vec2(optionItem->getPositionX(), optionItem->getPositionY() - 48));
	auto menu = Menu::create(newgameItem, optionItem, aboutItem, NULL);
	menu->setPosition(Vec2(size.width / 2, size.height / 2 + 50));
	addChild(menu);
	//²¥·Å±³¾°ÒôÀÖ
	AudioEngine::play2d("Music/mainMainMusic.mp3", true,0.2);
	return true;
}
void MainScene::menuNewCallback(Ref* pSender)
{
	AudioEngine::play2d("Music/buttonEffet.mp3", false, 0.5);
	auto gameScene = LevelOneScene::create();
	AudioEngine::stopAll();
	AudioEngine::play2d("Music/bgmusic.mp3", true,0.2);
	Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, gameScene));
}
void MainScene::menuAboutCallback(Ref* pSender)
{
	AudioEngine::play2d("Music/buttonEffet.mp3", false, 0.5);
	auto aboutScene = AboutScene::create();
	Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, aboutScene));
}
void MainScene::menuOptionCallback(Ref* pSender)
{
	AudioEngine::play2d("Music/buttonEffet.mp3", false, 0.5);
	auto optionScene = OptionScene::createScene();
	Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, optionScene));
}

