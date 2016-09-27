#include "Star.h"

bool Star::init()
{
	if(!Node::init())
		return false;

	star = Sprite::create("GamePlay/star_1.png");
	setSprite(star);

	return true;
}

void Star::setAction(float duration)
{
	auto rotate = RotateBy::create(duration, 360);
	auto action = RepeatForever::create(rotate);

	star->runAction(action);
}

void Star::setStarFrame(int num)
{
	char starName[30] = {0};
	sprintf(starName, "GamePlay/star_%d.png", num);
	star = Sprite::create(starName);
	setSprite(star);
}

void Star::setSprite(Sprite *sprite){
	star = sprite;
	this->removeAllChildren();
	this->addChild(star, 1);
}

Sprite* Star::getSprite()
{
	return star;
}