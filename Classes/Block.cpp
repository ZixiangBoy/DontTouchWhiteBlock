//
//  Block.cpp
//  DontTouchWhiteBlock
//
//  Created by apple on 15/5/24.
//
//

#include "Block.h"

Vector<Block*> * Block::blocks=new Vector<Block*>();


Block* Block::createWithArgs(Color3B color,Size size, std::string label, float fontSize, Color4B textColor){
    
    auto b=new Block();
    b->initWithArgs(color, size, label, fontSize, textColor);
    b->autorelease();
    
    blocks->pushBack(b);
    
    return b;
}

bool Block::initWithArgs(Color3B color,Size size,std::string label,float fontSize, Color4B textColor){
    Sprite::init();
    
    lineIndex=0;
    
    setContentSize(size);
    setAnchorPoint(Point::ZERO);
    setTextureRect(Rect(0,0,size.width,size.height));
    setColor(color);
    
    auto l=Label::create();
    l->setString(label);
    l->setSystemFontSize(fontSize);
    l->setTextColor(textColor);
    addChild(l);
    l->setPosition(size/2);
    
    return true;
}

void Block::moveDown(){
    this->lineIndex--;
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    
    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(),lineIndex*visibleSize.height/5))
             ,CallFunc::create([this](){
        if(lineIndex<0){
            this->removeBlock();
            
        }
        
    })
             ,NULL));
    
}

void Block::removeBlock(){
    removeFromParent();
    blocks->eraseObject(this);
}

void Block::setLineIndex(int value){
    lineIndex=value;
}

int Block::getLinendex(){
    return this->lineIndex;
}

Vector<Block*> * Block::getBlocks(){
    return Block::blocks;
}

