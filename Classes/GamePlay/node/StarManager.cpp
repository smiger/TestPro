#include "StarManager.h"
#include "../../Constant.h"

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

	setScore(0);
	//this->scheduleUpdate();

	return true;
}

void StarManager::createStar()
{
	Star* star = NULL;
	srand((unsigned)time(0));
	for(int i = 1; i <= starNum; i++)
	{
		star = Star::create();
		int num = 0;
		//num = CCRANDOM_0_1() * 5;
		num = rand()%5;
		//log("%d",rand());
		star->setStarFrame(num);
		star->setAction(2.0f);
		this->addChild(star, 2);
		//log("%f",star->getSprite()->getContentSize().width);
		int ran = size.width - 2 * star->getSprite()->getContentSize().width;
		float posX = rand() % ran + star->getSprite()->getContentSize().width;
		star->setPosition(posX, starDistance * i);
		if(i == 1)
			curStar = star;

		starList.push_back(star);

	}
	//记录生成新节点的位置
	spanY = starList.back()->getPosition().y;

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
void StarManager::setNextStar(Vec2 pos)
{
	if(isFirst)
	{
		isFirst = false;
	}
	else
	{
		CallFunc* span = CallFunc::create([=](){
			spanStar();
		});
		Star* star = NULL;
		Vec2 playerPos = curStar->convertToWorldSpace(pos);
		auto offset = size.height / 2 - playerPos.y;
		auto duration = abs(offset) / moveSpeed;
		//向下移动
		for(list<Star*>::iterator iter = starList.begin(); iter != starList.end(); iter++)
		{
			star = *iter;
			MoveBy* move = MoveBy::create(duration,Vec2(0,offset));
			Sequence* seq = Sequence::create(move, span, NULL);
			star->runAction(seq);
		}

	}
}


//圆形碰撞函数  
bool StarManager::isCircleCollision(Point pos2, float radius2)
{  
	//log("coll=%f,%f",pos2.x,pos2.y);
	//log("r=%f",radius2);
	Star* star = NULL;
	for(list<Star*>::iterator iter = starList.begin(); iter != starList.end(); iter++)
	{
		star = *iter;
		if(!isFirst && curStar == star)
			continue;
		Vec2 pos1 = star->getPosition();
		float radius1 = star->getSprite()->getContentSize().width / 2;
		//log("coll2=%f,%f",pos1.x,pos1.y);
		//log("r2=%f",radius1);
		//用三角型定理来计算圆心距,然后与半径和对比  
		if (sqrt(pow(pos1.x- pos2.x,2)+pow(pos1.y-pos2.y,2))>radius1+radius2) {
			continue;
		}
		curStar = star;
		return true;
	}
	return false;
}

void StarManager::spanStar()
{
	Star* star = NULL;
	while(starList.back()->getPosition().y < spanY)
	{
		//log("span");
		star = Star::create();
		int num = 0;
		num = rand()%5;
		star->setStarFrame(num);
		star->setAction(2.0f);
		this->addChild(star, 2);
		int ran = size.width - 2 * star->getSprite()->getContentSize().width;
		float posX = rand() % ran + star->getSprite()->getContentSize().width;
		star->setPosition(posX, starDistance + starList.back()->getPosition().y);
		starList.push_back(star);
		setScore(getScore() + 1);
		log("score=%ld",getScore());
	}


}