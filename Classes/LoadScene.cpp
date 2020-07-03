#include"LoadScene.h"
#include"MainScene.h"
#include"AudioEngine.h"
using namespace experimental;
Scene* LoadScene::createScene()
{
	return LoadScene::create();
}
bool LoadScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();
	//add bg
	auto layerSprite = Sprite::create("Loading.png");
	layerSprite->setPosition(Vec2(size.width/2,size.height/2));
	addChild(layerSprite);
	resourceLoading();
	//add flag
	auto loadlabel = Label::createWithTTF("Loading","fonts/Marker Felt.ttf",40);
	loadlabel->setColor(Color3B::WHITE);
	loadlabel->enableOutline(Color4B::RED,5);
	loadlabel->setPosition(Vec2(size.width/2,size.height/2));
	addChild(loadlabel);
	//add waiting
	auto waitinglabel = Label::createWithTTF("......", "fonts/Marker Felt.ttf", 40);
	waitinglabel->setColor(Color3B::WHITE);
	waitinglabel->enableOutline(Color4B::RED, 5);
	waitinglabel->setPosition(Vec2(size.width / 2+90, size.height / 2));
	addChild(waitinglabel);
	//add plane
	auto planeSprite = Sprite::createWithSpriteFrameName("E3.png");
	planeSprite->setRotation(90);
	planeSprite->setPosition(Vec2(50,200));
	addChild(planeSprite);
	//add action
	auto moveto = MoveTo::create(5,Vec2(270,200));
	auto blink = Blink::create(5,10);
	auto seq = Sequence::create(moveto, CallFunc::create(CC_CALLBACK_0(LoadScene::exchangeScene, this)),NULL);
	//run action
	waitinglabel->runAction(blink);
	planeSprite->runAction(seq);
}
void LoadScene::exchangeScene()
{
	auto scene = MainScene::create();
	Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, scene));

}
void LoadScene::resourceLoading()
{
	AudioEngine::preload("Music/bgmusic.mp3");
	AudioEngine::preload("Music/mainMainMusic.mp3");
	AudioEngine::preload("Music/buttonEffet.mp3");
	AudioEngine::preload("Music/explodeEffect.mp3");
	AudioEngine::preload("Music/fireEffect.mp3");
	AudioEngine::preload("Music/shipDestroyEffect.mp3");
	//预加载图像文件
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("textureTransparentPack.plist", "textureTransparentPack.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("textureOpaquePack.plist", "textureOpaquePack.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("b01.plist", "b01.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("explosion.plist", "explosion.png");
	//创建动画
	auto animation = Animation::create();
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(0.15f);
	animation->setLoops(1);
	for (int i = 1; i <= 9; i++)
	{
		std::string name = "explosion_0";
		name.append(std::to_string(i));
		name.append(".png");
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	for (int j = 10; j <= 35; j++)
	{
		std::string name = "explosion_";
		name.append(std::to_string(j));
		name.append(".png");
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	AnimationCache::getInstance()->addAnimation(animation, "explosion");
}
