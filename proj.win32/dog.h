#ifndef _GAME_DOG_H_
#define _GAME_DOG_H_

#include "cocos2d.h"
using namespace cocos2d;

class dog: public CCNode
{
public:
	dog(void);
	~dog(void);

	virtual void onEnter();
	virtual void onExit();

	void die();
	void restart();
	void move();
	void bullet(float sender);
	bool getlived();

private:
	CCSprite* body;
	CCSprite* boom;
	bool islived;
	int type;

	
};

#endif