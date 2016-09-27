#include "StarManager.h"

StarManager::StarManager()
	:isFirst(true)
	,curStar(NULL)
{
}
bool StarManager::init()
{
	if(!Node::init())
		return false;
	size = Director::getInstance()->getVisibleSize();
	createStar();

	return true;
}

void StarManager::createStar()
{
	Star* star = NULL;
	star = Star::create();
	star->setPosition(size.width/2,400);
	int num = 1;
	star->setStarFrame(num);
	star->setAction(2.0f);
	this->addChild(star);
	starList.push_back(star);



	log("%d",starList.size());

}
list<Star*> StarManager::getStarList()
{
	return starList;
}

Star* StarManager::getBeginStar()
{
	return (*starList.begin());
}
Star* StarManager::getCurStar()
{
	return curStar;
}
Vec2 StarManager::getBeginStarPos()
{
	return getBeginStar()->getPosition();
}
Vec2 StarManager::getCurStarPos()
{
	return getCurStar()->getPosition();
}
void StarManager::setNextStar()
{
	if(isFirst)
	{
		auto star = Star::create();
		star->setPosition(size.width/2,800);
		int num = 1;
		star->setStarFrame(num);
		star->setAction(2.0f);
		this->addChild(star);
		starList.push_back(star);
		isFirst = false;

	}
	else
	{
		list<Star*>::iterator iter = starList.begin();
		auto front = (Star*)*iter;
		iter = starList.erase(iter);
		starList.push_back(front);
	}
}


//圆形碰撞函数  
bool StarManager::isCircleCollision(Point pos2, float radius2)
{  
	log("coll=%f,%f",pos2.x,pos2.y);
	log("r=%f",radius2);
	Star* star;
	for(list<Star*>::iterator iter = starList.begin(); iter != starList.end(); iter++)
	{
		star = *iter;
		if(curStar == star)
			continue;
		Vec2 pos1 = star->getPosition();
		float radius1 = star->getSprite()->getContentSize().width / 2;
		log("coll2=%f,%f",pos1.x,pos1.y);
		log("r2=%f",radius1);
		//用三角型定理来计算圆心距,然后与半径和对比  
		if (sqrt(pow(pos1.x- pos2.x,2)+pow(pos1.y-pos2.y,2))>radius1+radius2) {
			return false;
		}
		curStar = star;
		return true;
	}
	return false;
}