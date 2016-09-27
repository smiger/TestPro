#ifndef __GP_MAIN_LAYER_H__
#define __GP_MAIN_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../node/Player.h"
#include "../node/StarManager.h"
USING_NS_CC;

class GPMainLayer : public Layer
{
public:
	GPMainLayer();
	virtual bool init();
	CREATE_FUNC(GPMainLayer);
	//static GPMainLayer* create(Scene * scene);
	// ����[����]
	void loadScene();
	// ����[��ť]
	void loadButton();
	// ����[player]
	void loadPlayer();
	// ����[����]
	void loadStar();
	void touchEvent(Ref *pSender, ui::Widget::TouchEventType type);

	bool isCircleCollision(Point pos1, float radius1, Point pos2, float radius2);
	virtual void update(float dt);
	void launch();
private:
	Size size;
	Node* m_res;
	bool isLand;
	Player* player;
	StarManager* starManager;
};

#endif
