#include "about.h"
#include "menu.h"

using namespace cocos2d;

CCScene* about::scene()
{
	CCScene* scene = CCScene::create();

	about* layer = about::create();

	scene->addChild(layer);

	return scene;
}

bool about::init()
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

	CCSprite* frame = CCSprite::create("tb.png");
	frame->setPosition(ccp(size.width/2,size.height/2));
	frame->setScale(0.5);
	this->addChild(frame,2,2);

	char notice[] = "Name:Meowstar Battel\n\nProgram:dserWei\n\nArt Design:dserWei\n\nCompany:Ozar Inc.\n\nPowered by cocos2d-x";
	//sprintf(notice,"Name:Meowstar Battel\n\nProgram:dserWei\n\nArt Design:dserWei\n\nCompany:Ozar Inc.\n\nPowered by cocos2d-x");
	CCLabelTTF* message = CCLabelTTF::create(notice,"Zapfino",40,CCSizeMake(400,400),kCCTextAlignmentLeft);
	message->setAnchorPoint(ccp(0,1));
	message->setPosition(ccp(50,600));
	message->setColor(ccc3(200,200,200));
	frame->addChild(message);

	CCSprite* title = CCSprite::create("about.png");
	title->setPosition(ccp(size.width/2,size.height-20));
	title->setScale(0.5);
	this->addChild(title,3,3);

	CCMenuItemImage* backItem = CCMenuItemImage::create("backA.png","backB.png",this,menu_selector(about::backCallback));
	backItem->setPosition(ccp(size.width-20,size.height-20));
	backItem->setScale(0.5);
	backItem->setEnabled(false);

	CCMenu* backMenu = CCMenu::create(backItem,NULL);
	backMenu->setPosition(ccp(0,0));
	this->addChild(backMenu,3,4);

	return true;
}

void about::backCallback(CCObject* sender)
{
	CCDirector::sharedDirector()->purgeCachedData();

	CCTransitionSlideInT* pScene = CCTransitionSlideInT::create(0.5,menu::scene());

	CCDirector::sharedDirector()->replaceScene(pScene);
}

void about::onEnter()
{
	CCLayer::onEnter();

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCNode* backItem = CCNode::getChildByTag(4);
	backItem->runAction(CCSequence::create(CCEaseElasticIn::create(CCFadeIn::create(0.5)),CCCallFuncN::create(this,callfuncN_selector(about::menuEnter)),NULL));
}

void about::menuEnter(CCNode* sender)
{
	CCNode* backMenu = this->getChildByTag(4);
	CCArray* tmp = backMenu->getChildren();

	((CCMenuItemImage*)tmp->objectAtIndex(0))->setEnabled(true);
}

void about::onExit()
{
	CCLayer::onExit();
}