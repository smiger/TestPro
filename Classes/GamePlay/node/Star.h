#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Star : public Node
{
public:
	CREATE_FUNC(Star);
	virtual bool init();

	void setAction(float duration);
	void setStarFrame(int num);
	void setSprite(Sprite *sprite);
	Sprite* getSprite();
private:
	Sprite* star;
};