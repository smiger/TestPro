#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Player : public Node
{
public:
	CREATE_FUNC(Player);
	virtual bool init();

	Sprite* getSprite();
	void setAction(Vec2 pos);
	void isCollision(Sprite* star);
	void jump(Sprite* star, Vec2 starPos);
	bool isOutofBounds();
private:
	Sprite* player;
	Size size;
};