#pragma once

#include "cocos2d.h"
#include "Star.h"
#include <list>
USING_NS_CC;
using namespace std;

class StarManager : public Node
{
public:
	StarManager();
	CREATE_FUNC(StarManager);
	virtual bool init();

	CC_SYNTHESIZE(long, score, Score);
	void createStar();
	list<Star*> getStarList();
	Star* getBeginStar();
	Star* getCurStar();
	Vec2 getBeginStarPos();
	Vec2 getCurStarPos();
	void setNextStar(Vec2 pos);
	bool isCircleCollision(Point pos2, float radius2);

	void spanStar();
private:
	Size size;
	list<Star *> starList;
	bool isFirst;
	Star* curStar;
	float spanY;
};