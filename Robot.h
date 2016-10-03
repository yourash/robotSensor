#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "cocos2d.h"
#include "RedRay.h"

class Robot
{
public:
	Robot(cocos2d::Layer* layer);
	void changeWidth(int percentX, int percentY);
	void changeHeight(int percentX, int percentY);
	void changeRotation(int percent);
	void changeStep(int percent);
	float getStepX();
	float getStepY();
	void makeStep();
	void rayOn();
	void makeRayRotation(int rotation);
	void rayOff();
	cocos2d::Vec2 getPosition();
	~Robot();
private:
	float stepLength;
 	cocos2d::Sprite	*mrRobot;
 	cocos2d::Size visibleSize;
 	float rotation;
 	cocos2d::Layer* aLayer;
 	RedRay* aRay;
};

#endif // __ROBOT_H__