#ifndef __GAME_PLAY_H__
#define __GAME_PLAY_H__

#include "cocos2d.h"
//#include "layer/GPBackgroundLayer.h"
#include "layer/GPMainLayer.h"
USING_NS_CC;

class GamePlay : public Layer
{
public:
	GamePlay();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GamePlay);
	// 加载[背景层]
	//void loadBackgroundLayer();
	// 加载[游戏主层]
	void loadMainLayer();
private:
	//GPBackgroundLayer* backgroundLayer;
	GPMainLayer* mainLayer;
};

#endif
