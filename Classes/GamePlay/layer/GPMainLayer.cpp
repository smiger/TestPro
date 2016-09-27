#include "GPMainLayer.h"
#include "cocostudio/CocoStudio.h"



GPMainLayer::GPMainLayer()
	:isLand(false)
{
}
//GPMainLayer* GPMainLayer::create(Scene* scene)
//{
//	GPMainLayer *pRet = new GPMainLayer();
//	if (pRet && pRet->init(scene))
//	{
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		delete pRet;
//		pRet = NULL;
//		return NULL;
//	}
//}
bool GPMainLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	size = Director::getInstance()->getWinSize();

	// 加载[场景]
	loadScene();
	// 加载[按钮]
	loadButton();


	// 加载[星球]
	loadStar();
		// 加载[player]
	loadPlayer();

	this->schedule(schedule_selector(GPMainLayer::update), 0.01f, kRepeatForever, 0);
	return true;
}
void GPMainLayer::loadScene()
{
	m_res=CSLoader::createNode("GamePlay/GamePlay.csb");
	addChild(m_res);
}
void GPMainLayer::loadButton()
{
	ui::Button* control_1 = dynamic_cast<ui::Button*>(m_res->getChildByName("Button_1"));
	control_1->addTouchEventListener(CC_CALLBACK_2(GPMainLayer::touchEvent, this));
	ui::Button* control_2 = dynamic_cast<ui::Button*>(m_res->getChildByName("Button_2"));
	control_2->addTouchEventListener(CC_CALLBACK_2(GPMainLayer::touchEvent, this));
}
void GPMainLayer::loadPlayer()
{
	player = Player::create();
	this->addChild(player);
	player->setAction(starManager->getBeginStarPos());
}
void GPMainLayer::loadStar()
{
	starManager = StarManager::create();
	this->addChild(starManager);
	log("%f",starManager->getBeginStarPos().y);
	//log("%f",starManager->getCurStarPos().y);
}
void GPMainLayer::touchEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
	ui::Button* pBt = dynamic_cast<ui::Button*>(pSender);

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if(pBt->getName() == "Button_1")
		{
			log("bbb");
			launch();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
//
////圆形碰撞函数  
//bool GPMainLayer::isCircleCollision(Point pos1, float radius1, Point pos2, float radius2)
//{  
//	//用三角型定理来计算圆心距,然后与半径和对比  
//	if (sqrt(pow(pos1.x- pos2.x,2)+pow(pos1.y-pos2.y,2))>radius1+radius2) {
//		return false;
//	}
//	return true;
//}  

// 更新[游戏逻辑]
void GPMainLayer::update(float dt)
{
	if(!isLand)
		if(starManager->isCircleCollision(player->getSprite()->getPosition(),player->getSprite()->getContentSize().width/2))
		{
			log("aaa");
			player->isCollision(starManager->getCurStar()->getSprite());
			isLand = true;

			starManager->setNextStar();
			log("%f",starManager->getBeginStarPos().y);
			log("%f",starManager->getCurStarPos().y);
		}
}
void GPMainLayer::launch()
{
	if(isLand)
	{
		player->jump(starManager->getBeginStar()->getSprite(), starManager->getBeginStarPos());
		isLand = false;
	}
}