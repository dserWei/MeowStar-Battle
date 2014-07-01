#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include "cat.h"
#include "dog.h"
#include "fishbone.h"
#include "tube.h"
#include "mark.h"
#include "cocos2d.h"
using namespace cocos2d;

class game: public CCLayer
{
public:

	static CCScene* scene();

	virtual bool init();
	virtual void update(float time);

	virtual void onEnter();
	virtual void onExit();

	void backCallback(CCObject* sender);

	bool getover();
	void setover();

	bool isCollided(CCPoint p1,CCPoint p2,int h1,int w1,int h2,int w2);
	void hurt();
	void reset(float sender);

	void releaseFishbone(int x, int y);
	void releaseTube(int x, int y);

	CREATE_FUNC(game);

private:
	bool isover;
	bool ishurt;
	int life;

	CCSprite* bg1, * bg2, * blood1, * blood2, * blood3;
	mark* mk;
	cat* hero;
	CCArray* dogs, * fishbones, * tubes;
	CCSprite* over;
	CCMenu* Back, * backMenu;
};

#endif