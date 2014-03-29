#include "menu.h"

using namespace cocos2d;

CCScene* menu::scene()
{
	CCScene* pScene = CCScene::create();

	menu* pLayer = menu::create();

	pScene->addChild(pLayer);

	return pScene;
}

bool menu::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(size.width/2,size.height/2));
	bg->setScale(0.5);
	this->addChild(bg,0,0);

	CCSprite* bgStar = CCSprite::create("moon.png");
	bgStar->setAnchorPoint(ccp(0.5,0));
	bgStar->setPosition(ccp(size.width/3*2,0));
	bgStar->setScale(0.5);
	this->addChild(bgStar);

	CCNode* title = CCNode::create();
	title->setContentSize(CCSizeMake(size.width-40,50));
	title->setPosition(ccp(size.width/2,size.height-80));
	
	CCSprite* label1 = CCSprite::create("meowstar.png");
	label1->setPosition(ccp(0,30));
	label1->setScale(0.5);
	title->addChild(label1);

	CCSprite* label2 = CCSprite::create("battle.png");
	label2->setPosition(ccp(0,-30));
	label2->setScale(0.5);
	title->addChild(label2);

	this->addChild(title,2,2);

	return true;
}