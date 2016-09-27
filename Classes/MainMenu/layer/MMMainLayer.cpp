#include "MMMainLayer.h"
#include "cocostudio/CocoStudio.h"

#include "../../GamePlay/GamePlay.h"

bool MMMainLayer::init()
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

	return true;
}
void MMMainLayer::loadScene()
{
	m_res=CSLoader::createNode("MainMenu/MainMenu.csb");
	this->addChild(m_res);
}
void MMMainLayer::loadButton()
{
	ui::Button* start = dynamic_cast<ui::Button*>(m_res->getChildByName("Button_Start"));
	start->addTouchEventListener(CC_CALLBACK_2(MMMainLayer::touchEvent, this));
}
void MMMainLayer::touchEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
	ui::Button* pBt = dynamic_cast<ui::Button*>(pSender);

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if(pBt->getName() == "Button_Start")
		{
			auto playScene = TransitionFade::create(1, GamePlay::createScene());
			Director::getInstance()->replaceScene(playScene);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


