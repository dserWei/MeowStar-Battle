#include "menu.h"
#include "about.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
	this->addChild(bgStar,1,1);

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

	this->addChild(title,1,2);

	CCMenuItemImage* newItem = CCMenuItemImage::create("newGameA.png","newGameB.png",this,menu_selector(menu::newCallback));
	newItem->setPosition(ccp(size.width/2,size.height/2-20));
	newItem->setScale(0.6);
	//newItem->setEnabled(false);

	CCMenuItemImage* continueItem = CCMenuItemImage::create("ContinueA.png","ContinueB.png",this,menu_selector(menu::continueCallback));
	continueItem->setPosition(ccp(size.width/2,size.height/2-80));
	continueItem->setScale(0.6);
	//continueItem->setEnabled(false);

	CCMenuItemImage* aboutItem = CCMenuItemImage::create("aboutA.png","aboutB.png",this,menu_selector(menu::aboutCallback));
	aboutItem->setPosition(ccp(size.width/2,size.height/2-140));
	aboutItem->setScale(0.6);
	//aboutItem->setEnabled(false);

	soundItem = CCMenuItemImage::create("sound-on-A.png","sound-on-B.png",this,menu_selector(menu::soundCallback));
	soundItem->setPosition(ccp(40,40));
	soundItem->setScale(0.6);
	//soundItem->setEnabled(false);

	CCMenu* mainMenu = CCMenu::create(newItem,continueItem,aboutItem,soundItem,NULL);
	mainMenu->setPosition(ccp(0,0));
	this->addChild(mainMenu,2,3);

	sound = true;
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background.mp3");
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3",true);

	return true;
}

void menu::onEnter()
{
	CCLayer::onEnter();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCNode* mainMenu = this->getChildByTag(3);
	mainMenu->setPositionX(-200);
	mainMenu->runAction(CCMoveTo::create(0.5,ccp(0,0)));

	CCNode* title = this->getChildByTag(2);
	title->setPositionY(size.height+20);
	title->runAction(CCMoveBy::create(0.5,ccp(0,-100)));

	CCNode* bgStar = this->getChildByTag(1);
	bgStar->setPositionX(size.width/3*4);
	bgStar->runAction(CCMoveBy::create(0.5,ccp(-size.width/3*2,0)));

}

/*void menu::menuEnter(CCNode* sender)
{
	CCNode* mainMenu = this->getChildByTag(3);
	CCArray* temp = mainMenu->getChildren();
	
	for(int i = 0; i < temp->count(); i++)
	{
		((CCMenuItemImage*)temp->objectAtIndex(i))->setEnabled(true);
	}
}*/

void menu::onExit()
{
	CCLayer::onExit();
}

void menu::newCallback(CCObject* sender)
{
}

void menu::continueCallback(CCObject* sender)
{
}

void menu::aboutCallback(CCObject* sender)
{
	CCDirector::sharedDirector()->purgeCachedData();

	CCTransitionSlideInB* tScene = CCTransitionSlideInB::create(0.5,about::scene());

	CCDirector::sharedDirector()->replaceScene(tScene);
}

void menu::soundCallback(CCObject* sender)
{
	if(menu::sound)
	{
		menu::soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
		menu::soundItem->setSelectedImage(CCSprite::create("sound-off-B.png"));
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

		menu::sound = false;
	}
	else
	{
		menu::soundItem->setNormalImage(CCSprite::create("sound-on-A.png"));
		menu::soundItem->setSelectedImage(CCSprite::create("sound-on-B.png"));
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

		menu::sound = true;
	}
}