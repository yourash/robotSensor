#ifndef __REDRAY_H__
#define __REDRAY_H__

#include "cocos2d.h"

class RedRay
{
public:
	RedRay();
	RedRay(cocos2d::Layer* layer,cocos2d::Vec2 robotPos,float angle);
	void removeRay();
	void rotateRay(cocos2d::Vec2 robotPos ,float rotation);
	~RedRay();
private:
	cocos2d::Size visibleSize;	
	cocos2d::DrawNode* ray;
	cocos2d::Layer* aLayer;
};

#endif // __REDRAY_H__