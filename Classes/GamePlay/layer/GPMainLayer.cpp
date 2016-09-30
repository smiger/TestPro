#include "GPMainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "../../MainMenu/MainMenu.h"



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

	// ����[����]
	loadScene();
	// ����[��ť]
	loadButton();


	// ����[����]
	loadStar();
	// ����[player]
	loadPlayer();

	// ����һ���¼�����������Ϊ OneByOne �ĵ��㴥��
    auto listener = EventListenerTouchOneByOne::create();
    // �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û
    listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GPMainLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GPMainLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GPMainLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GPMainLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_res);

	this->schedule(schedule_selector(GPMainLayer::update), 0.01f, kRepeatForever, 0);
	return true;
}
void GPMainLayer::loadScene()
{
	m_res=CSLoader::createNode("GamePlay/GamePlay.csb");
	addChild(m_res);
	log("m_res=%d",m_res->getGlobalZOrder());
}
void GPMainLayer::loadButton()
{

	ui::Button* control_3 = dynamic_cast<ui::Button*>(m_res->getChildByName("Button_1"));
	control_3->addTouchEventListener(CC_CALLBACK_2(GPMainLayer::touchEvent, this));
	auto control_4 = dynamic_cast<Sprite*>(m_res->getChildByName("test1"));
	//control_4->addTouchEventListener(CC_CALLBACK_2(GPMainLayer::touchEvent, this));
	control_3->setGlobalZOrder(10);
	control_4->setGlobalZOrder(10);
	log("control=%f,%f",control_3->getGlobalZOrder(),control_4->getGlobalZOrder());
	
	
	//Sprite* sprite = dynamic_cast<Sprite*>(m_res->getChildByName("Sprite_1"));
	//scoreText = dynamic_cast<ui::Text*>(sprite->getChildByName("Text_Score"));
	scoreText = Label::createWithSystemFont("", "Arial-BoldMT", 72);
	scoreText->setPosition(size.width/2, size.height*0.9f);
	this->addChild(scoreText,10);
	//auto label = dynamic_cast<ui::TextAtlas*>(m_res->getChildByName("Label"));

	//label->setGlobalZOrder(10);
	//sprite->setPositionZ(10);

	auto gameover = m_res->getChildByName("GameOver");
	ui::Button* control_1 = dynamic_cast<ui::Button*>(gameover->getChildByName("Button_1"));
	control_1->addTouchEventListener(CC_CALLBACK_2(GPMainLayer::touchEvent, this));
	ui::Button* control_2 = dynamic_cast<ui::Button*>(gameover->getChildByName("Button_2"));
	control_2->addTouchEventListener(CC_CALLBACK_2(GPMainLayer::touchEvent, this));
	gameover->setLocalZOrder(8888);
	control_2->setLocalZOrder(8888);
}
void GPMainLayer::loadPlayer()
{
	player = Player::create();
	addChild(player, 2);
	player->setAction(starManager->getCurStarPos());
	log("player=%d",player->getGlobalZOrder());
}
void GPMainLayer::loadStar()
{
	starManager = StarManager::create();
	addChild(starManager);
	log("starManager=%d",starManager->getGlobalZOrder());
	//log("%f",starManager->getBeginStarPos().y);
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
			restart();
		}
		else if(pBt->getName() == "Button_2")
		{
			exit();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
//
////Բ����ײ����  
//bool GPMainLayer::isCircleCollision(Point pos1, float radius1, Point pos2, float radius2)
//{  
//	//�������Ͷ���������Բ�ľ�,Ȼ����뾶�ͶԱ�  
//	if (sqrt(pow(pos1.x- pos2.x,2)+pow(pos1.y-pos2.y,2))>radius1+radius2) {
//		return false;
//	}
//	return true;
//}  

// ����[��Ϸ�߼�]
void GPMainLayer::update(float dt)
{
	if(!isLand)
	{
		if(starManager->isCircleCollision(player->getSprite()->getPosition(),player->getSprite()->getContentSize().width/2))
		{
			//log("aaa");
			player->isCollision(starManager->getCurStar()->getSprite());
			isLand = true;

			starManager->setNextStar(player->getSprite()->getPosition());
			//log("%f",starManager->getBeginStarPos().y);
			//log("%f",starManager->getCurStarPos().y);

		}
	}

	//���·���
	char score[10] = {0};
	sprintf(score, "%ld", starManager->getScore());
	scoreText->setString(score);
	//����Ƿ�Խ��
	if(player->isOutofBounds())
	{
		log("over");
		unschedule(schedule_selector(GPMainLayer::update));
		auto gameover = m_res->getChildByName("GameOver");
		gameover->setVisible(true);
	}

}
void GPMainLayer::launch()
{
	if(isLand)
	{
		player->jump(starManager->getCurStar()->getSprite(), starManager->getCurStarPos());
		isLand = false;
	}
}

bool GPMainLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	launch();
	return true;
}

void GPMainLayer::restart()
{
}

void GPMainLayer::exit()
{
	auto scene = TransitionFade::create(1, MainMenu::createScene());
	Director::getInstance()->replaceScene(scene);
}