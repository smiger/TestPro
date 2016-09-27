#ifndef __MM_MAIN_LAYER_H__
#define __MM_MAIN_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class MMMainLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MMMainLayer);
	
	// 加载[场景]
	void loadScene();
	// 加载[按钮]
	void loadButton();
	void touchEvent(Ref *pSender, ui::Widget::TouchEventType type);
private:
	Size size;
	Node* m_res;
};

#endif
