#include "MainMenu.h"



MainMenu::MainMenu()
:mainLayer(NULL)             // ÓÎÏ·²ã
{
}
Scene * MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;

}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/parkour.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("octopus.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist");
	// ¼ÓÔØ[±³¾°²ã]
	//loadBackgroundLayer();
	// ¼ÓÔØ[ÓÎÏ·Ö÷²ã]
	loadMainLayer();
	return true;
}
//void MainMenu::loadBackgroundLayer()
//{
//	backgroundLayer = MMBackgroundLayer::create();
//	this->addChild(backgroundLayer);
//}
void MainMenu::loadMainLayer()
{
	mainLayer = MMMainLayer::create();
	this->addChild(mainLayer);
}

