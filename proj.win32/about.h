#ifndef _GAME_ABOUT_H_
#define _GAME_ABOUT_H_

#include "cocos2d.h"
using namespace cocos2d;

class about: public CCLayer
{
public:
	static CCScene* scene();

	virtual bool init();

	virtual void onEnter();
	void menuEnter(CCNode* sender);

	virtual void onExit();

	void backCallback(CCObject* sender);

	CREATE_FUNC(about);
};

#endif