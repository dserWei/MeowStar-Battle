#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

static bool sound = true;
extern bool ispaused;

class menu : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();

	void newCallback(CCObject* sender);
	void continueCallback(CCObject* sender); 
	void aboutCallback(CCObject* sender);
	void soundCallback(CCObject* sender);

	virtual void onEnter();
	//void menuEnter(CCNode* sender);

	virtual void onExit();

	CREATE_FUNC(menu);

private:
	cocos2d::CCMenuItemImage* soundItem;
};

#endif