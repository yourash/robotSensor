#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Robot.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainScene);

    void sizeSliderEvent(Ref *sender, ui::Slider::EventType type);
    void rotationSliderEvent(Ref *sender, ui::Slider::EventType type);
    void stepSliderEvent(Ref *sender, ui::Slider::EventType type);

    void START(cocos2d::Ref* pSender);

private:
	Robot *mrRobot;
	cocos2d::Label* sizeLabel;
	cocos2d::Label* rotationLabel;
	cocos2d::Label* stepLabel;
	int robotSize, robotRotation, robotStep;
	//__String *tempSize;
};

#endif // __MAIN_SCENE_H__
