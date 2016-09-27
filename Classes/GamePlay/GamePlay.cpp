#include "GamePlay.h"

GamePlay::GamePlay()
{
}

Scene * GamePlay::createScene()
{
	auto scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vect(0, -1450));
	auto layer = GamePlay::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlay::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// ¼ÓÔØ[±³¾°²ã]
	//loadBackgroundLayer();
	// ¼ÓÔØ[ÓÎÏ·Ö÷²ã]
	loadMainLayer();
	
	return true;
}

//void GamePlay::loadBackgroundLayer()
//{
//	backgroundLayer = GPBackgroundLayer::create();
//	this->addChild(backgroundLayer);
//}
void GamePlay::loadMainLayer()
{
	mainLayer = GPMainLayer::create();
	this->addChild(mainLayer);
}