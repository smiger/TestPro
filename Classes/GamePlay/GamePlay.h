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
	// ����[������]
	//void loadBackgroundLayer();
	// ����[��Ϸ����]
	void loadMainLayer();
private:
	//GPBackgroundLayer* backgroundLayer;
	GPMainLayer* mainLayer;
};

#endif
