#include "Player.h"

bool Player::init()
{
	if(!Node::init())
		return false;
	size = Director::getInstance()->getWinSize();

	player= Sprite::create("GamePlay/player.png");
	player->setPosition(Vec2(100,100));
	this->addChild(player);

	return true;
}
void Player::setAction(Vec2 pos)
{
	auto move = MoveTo::create(2.0f,pos);
	player->runAction(move);
}
void Player::isCollision(Sprite* star)
{
		player->stopAllActions();
		Vec2 playerPos = player->getPosition();
		player->removeFromParent();
		player= Sprite::create("GamePlay/player.png");
		player->setPosition(star->convertToNodeSpace(playerPos));
		star->addChild(player);
}
void Player::jump(Sprite* star, Vec2 starPos)
{
	log("==%f,%f",starPos.x,starPos.y);
	Vec2 playerPos = star->convertToWorldSpace(player->getPosition());
	log("1==%f,%f",playerPos.x,playerPos.y);
	Vec2 playerPos2 = star->convertToWorldSpace(playerPos);
	log("2==%f,%f",playerPos2.x,playerPos2.y);
	
	Vec2 jumpPos = playerPos - starPos;
	float rotateRadians = jumpPos.getAngle();
	float rotateDegrees = CC_RADIANS_TO_DEGREES(rotateRadians);
	log("%f",rotateDegrees);
	//float aa = tan(rotateDegrees) * 400;
	//Vec2 dest = starPos + 10 * jumpPos;
	float desX = 1000 * cosf(rotateRadians);
	float desY = 1000 * sinf(rotateRadians);
	log("%f,%f",desX,desY);
	player->removeFromParent();
	player = Sprite::create("GamePlay/player.png");
	this->addChild(player);
	player->setPosition(playerPos);
	auto move = MoveBy::create(2.0f,Vec2(desX, desY));
	player->runAction(move);
}
Sprite* Player::getSprite()
{
	return player;
}
bool Player::isOutofBounds()
{
	if(player->getPosition().x < 0 || player->getPosition().x > size.width || player->getPosition().y < 0 || player->getPosition().y > size.height)
		return true;
	return false;
}