#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "2d/CCDrawingPrimitives.h"

#define SCORE_FONT_SIZE 0.04

bool rayIsOn=false;

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //BACKGROUND    

    {
        backGround = Sprite::create("background.png");
        backGround->setPosition(Vec2((visibleSize.width/2), (visibleSize.height/2)));
        backGround->setScale(visibleSize.width/backGround->getContentSize().width,visibleSize.height/backGround->getContentSize().height);
        this->addChild(backGround, -1);
    }

    //MENU

        //WIDTH
    {
        ui::Slider *widthSlider=ui::Slider::create();
        widthSlider->loadBarTexture("bar.png");
        widthSlider->loadSlidBallTextureNormal("slider.png");
        widthSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.95));
        widthSlider->setScale(1.8,1);
        this->addChild(widthSlider);

        widthSlider->addEventListener(CC_CALLBACK_2(MainScene::widthSliderEvent, this));
        
        widthLabel = Label::createWithTTF( "Width: 0", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        widthLabel->setColor(Color3B::WHITE);
        widthLabel->setPosition(Point(visibleSize.width*0.92, visibleSize.height * 0.95));

        this->addChild(widthLabel);
    }

        //HEIGHT
    {
        ui::Slider *heightSlider=ui::Slider::create();
        heightSlider->loadBarTexture("bar.png");
        heightSlider->loadSlidBallTextureNormal("slider.png");
        heightSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.85));
        heightSlider->setScale(1.8,1);
        this->addChild(heightSlider);

        heightSlider->addEventListener(CC_CALLBACK_2(MainScene::heightSliderEvent, this));
        
        heightLabel = Label::createWithTTF( "Height: 0", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        heightLabel->setColor(Color3B::WHITE);
        heightLabel->setPosition(Point(visibleSize.width*0.92, visibleSize.height * 0.85));

        this->addChild(heightLabel);       
    }

        //ROTATION
    {
        ui::Slider *rotationSlider=ui::Slider::create();
        rotationSlider->loadBarTexture("bar.png");
        rotationSlider->loadSlidBallTextureNormal("slider.png");
        rotationSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.75));
        rotationSlider->setScale(1.8,1);
        this->addChild(rotationSlider);

        rotationSlider->addEventListener(CC_CALLBACK_2(MainScene::rotationSliderEvent, this));

        rotationLabel = Label::createWithTTF( "Rotation:  0'", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        rotationLabel->setColor(Color3B::WHITE );
        rotationLabel->setPosition(Point(visibleSize.width*0.92, visibleSize.height * 0.75));
        
        this->addChild(rotationLabel);
    }

        //STEP
    {
        ui::Slider *stepSlider=ui::Slider::create();
        stepSlider->loadBarTexture("bar.png");
        stepSlider->loadSlidBallTextureNormal("slider.png");
        stepSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.65));
        stepSlider->setScale(1.8,1);
        this->addChild(stepSlider);

        stepSlider->addEventListener(CC_CALLBACK_2(MainScene::stepSliderEvent, this));

        stepLabel = Label::createWithTTF( "Step:  0", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        stepLabel->setColor(Color3B::WHITE );
        stepLabel->setPosition(Point(visibleSize.width*0.92, visibleSize.height * 0.65));
        
        this->addChild(stepLabel);
    }

        //RAYROTATIONANGLE
    {
        ui::Slider *angleSlider=ui::Slider::create();
        angleSlider->loadBarTexture("bar.png");
        angleSlider->loadSlidBallTextureNormal("slider.png");
        angleSlider->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height*0.55));
        angleSlider->setScale(1.8,1);
        this->addChild(angleSlider);

        angleSlider->addEventListener(CC_CALLBACK_2(MainScene::changeAngle, this));

        angleLabel = Label::createWithTTF( "Angle:  0'", "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
        angleLabel->setColor(Color3B::WHITE );
        angleLabel->setPosition(Point(visibleSize.width*0.92, visibleSize.height * 0.55));
        
        this->addChild(angleLabel);
    }

        //START
    {
        auto startItem = MenuItemImage::create("startbutton.png","startbutton.png",CC_CALLBACK_1(MainScene::START, this));
    
        startItem->setPosition(Vec2(visibleSize.width*0.9,visibleSize.height*0.15));

        auto startButton = Menu::create(startItem, NULL);
        startButton->setPosition(Vec2::ZERO);
        this->addChild(startButton, 1);
    }

        //RAY
    {
        auto rayItem = MenuItemImage::create("raybutton.png","raybutton.png",CC_CALLBACK_1(MainScene::RAY, this));
    
        rayItem->setPosition(Vec2(visibleSize.width*0.9,visibleSize.height*0.25));

        auto rayButton = Menu::create(rayItem, NULL);
        rayButton->setPosition(Vec2::ZERO);
        this->addChild(rayButton, 1); 
    }

    //OBJECT_INIT

    mrRobot=new Robot(this);


    rotationAngle=90;
    this->scheduleUpdate();
    
    return true;
}

int rotation=0;

void MainScene::update(float delta)
{
    Node::update(delta);
    if(rayIsOn)
    {
        mrRobot->makeRayRotation(rotation);
        rotation=rotation+rotationAngle;
    }
    Layer::update(delta);
}


void MainScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainScene::widthSliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        mrRobot->changeWidth(percent,robotHeight);
        robotWidth=percent;
        widthLabel->setString("Width: "+(std::to_string(robotWidth)));
    }
}

void MainScene::heightSliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        mrRobot->changeHeight(robotWidth,percent);
        robotHeight=percent;
        heightLabel->setString("Height: "+(std::to_string(robotHeight)));
    }
}

void MainScene::rotationSliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        mrRobot->changeRotation(percent);
        robotRotation=percent*3.6;
        rotationLabel->setString("Rotation: "+(std::to_string(robotRotation))+"'");
    }
}

void MainScene::stepSliderEvent(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        mrRobot->changeStep(percent);
        robotStep=percent;
        stepLabel->setString("Step: "+(std::to_string(robotStep)));
    }
}

void MainScene::changeAngle(Ref *sender, ui::Slider::EventType type)
{
    if(type==ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider *slider = dynamic_cast<ui::Slider *>(sender);
        int percent = slider->getPercent();
        rotationAngle=percent*0.9;
        angleLabel->setString("Angle: "+(std::to_string(rotationAngle))+"'");
    }
}

void MainScene::START(cocos2d::Ref* pSender)
{
    if(!rayIsOn)
        mrRobot->makeStep();
}

void MainScene::RAY(cocos2d::Ref* pSender)
{   
    if(!rayIsOn)
    {
        mrRobot->rayOn();
        rayIsOn=true;
    }
    else
    {
        mrRobot->rayOff();
        rayIsOn=false;
    }
}