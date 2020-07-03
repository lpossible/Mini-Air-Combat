#include"EnemyBulletSprite.h"

bool EnemyBulletSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}
EnemyBulletSprite* EnemyBulletSprite::createEnemyBullet(SpriteFrame* spriteFrame)
{
    EnemyBulletSprite* sprite = new (std::nothrow) EnemyBulletSprite();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void EnemyBulletSprite::move()
{
    auto const pos = this->getPosition();
    this->setPosition(Vec2(pos.x + speed[0], pos.y + speed[1]));
}
