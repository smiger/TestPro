#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
//#include "layer/MMBackgroundLayer.h"
#include "layer/MMMainLayer.h"
USING_NS_CC;

class MainMenu : public Layer
{
public:
	MainMenu();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenu);
	//void loadBackgroundLayer();
	void loadMainLayer();
private:
	//MMBackgroundLayer* backgroundLayer;
	MMMainLayer* mainLayer;


};

#endif
