#ifndef __GAME_MENU_H__
#define __GAME_MENU_H__

#include "cocos2d.h"

class menu : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();

	CREATE_FUNC(menu);
};

#endif