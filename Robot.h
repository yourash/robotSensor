#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "cocos2d.h"

class Robot
{
public:
	Robot(cocos2d::Layer* layer);
	void changeSize(int percent);
	void changeRotation(int percent);
	void changeStep(int percent);
	float getStepX();
	float getStepY();
	void makeStep();
	~Robot();
private:
	float stepLength;
 	cocos2d::Sprite	*mrRobot;
 	cocos2d::Size visibleSize;
 	float rotation;
};

#endif // __ROBOT_H__