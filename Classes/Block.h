//
//  Block.h
//  DontTouchWhiteBlock
//
//  Created by apple on 15/5/24.
//
//

#ifndef __DontTouchWhiteBlock__Block__
#define __DontTouchWhiteBlock__Block__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class Block : public Sprite {
    
private:
    static Vector<Block*>* blocks;
    int lineIndex;
    
public:
    static Vector<Block*>* getBlocks();
    
    void removeBlock();
    
    static Block* createWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    virtual bool initWithArgs(Color3B color,Size size,std::string label,float fontSize,Color4B textColor);
    
    int getLinendex();
    
    void setLineIndex(int value);
    
    void moveDown();
};

#endif /* defined(__DontTouchWhiteBlock__Block__) */
