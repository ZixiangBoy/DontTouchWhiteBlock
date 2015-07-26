#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    srand(time(NULL));
    
    visibleSize=Director::getInstance()->getVisibleSize();
    
    gameLayer=Node::create();
    
    addChild(gameLayer);
    timerLabel=Label::create();
    timerLabel->setTextColor(Color4B::BLUE);
    timerLabel->setSystemFontSize(40);
    timerLabel->setPosition(visibleSize.width-100,visibleSize.height-100);
    timerLabel->setString("0.00");
    addChild(timerLabel);
    
    startGame();
    
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[this](Touch* t,Event* e){
        //log("touch");
        
        auto blocks=Block::getBlocks();
        
        Block * b;
        
        for (auto it=blocks->begin(); it!=blocks->end(); it++) {
            b=*it;
            
            
            if(b->getLinendex()==1 &&
               b->getBoundingBox().containsPoint((t->getLocation()))){
                
                   if(b->getColor()==Color3B::BLACK){
                       if(!timerRunning){
                           this->startTimer();
                       }
                       b->setColor(Color3B::GRAY);
                       this->moveDown();
                   }
                   else if(b->getColor()==Color3B::GREEN){
                       this->moveDown();
                       this->StopTimer();
                   }
                   else{
                       MessageBox("game over", "");
                   }
                
                break;
               }
            
        }
        
        
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::addStartLine(){
    auto b=Block::createWithArgs(Color3B::YELLOW,Size(visibleSize.width, visibleSize.height/5),"",20,Color4B::BLACK);
    gameLayer->addChild(b);
    b->setLineIndex(0);
}

void HelloWorld::addEndLine(){
    auto b=Block::createWithArgs(Color3B::GREEN, visibleSize, "Game Over", 32, Color4B::BLACK);
    gameLayer->addChild(b);
    b->setLineIndex(4);
}

void HelloWorld::addNomalLine(int lineIndex){
    Block* b;
    
    linesCount++;
    
    int blackIndex=rand()%4;
    
    for (int i=0; i<4; i++) {
        auto color= blackIndex==i ? Color3B::BLACK : Color3B::WHITE;
    
        b=Block::createWithArgs(color,Size(visibleSize.width/4-1,visibleSize.height/5-1), "", 20, Color4B::BLACK);
        gameLayer->addChild(b);
        
        
        b->setPosition(i*visibleSize.width/4,lineIndex*visibleSize.height/5);
        b->setLineIndex(lineIndex);
    }
}

void HelloWorld::moveDown(){
    
    if(linesCount<50){
        addNomalLine(5);
    }else if(!showEnd){
        addEndLine();
        showEnd=true;
        
    }
    
    auto bs=Block::getBlocks();
    for (auto it=bs->begin(); it!=bs->end(); it++) {
        (*it)->moveDown();
    }
}

void HelloWorld::startGame(){
    showEnd=false;
    timerRunning=false;
    
    addStartLine();
    addNomalLine(1);
    addNomalLine(2);
    addNomalLine(3);
    addNomalLine(4);
}

void HelloWorld::startTimer(){
    if(!timerRunning){
        scheduleUpdate();
        startTime=clock();
        timerRunning=true;
    }
}

void HelloWorld::StopTimer(){
    if(timerRunning){
        unscheduleUpdate();
        
        timerRunning=false;
    }
    
}

void HelloWorld::update(float dt){
    long offset=clock()- startTime;
    
    timerLabel->setString(StringUtils::format("%g",(double)offset/1000000));
    
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
