//
//  Tri.h
//  loadvidoe02_colorshift
//
//  Created by Weibo Chen on 2019/2/26.
//

#ifndef _TRI
#define _TRI
#include "ofMain.h"
class Tri
{
public:
    Tri();
    ~Tri();
    void setup();
    void update();
    void draw();
    float x1 = ofRandomWidth();
    float x2 = ofRandomWidth();
    float x3 = ofRandomWidth();
    float y1 = ofRandomHeight();
    float y2 = ofRandomHeight();
    float y3 = ofRandomHeight();
    float speedX1 = ofRandom(-1, 1);
    float speedX2 = ofRandom(-1, 1);
    float speedX3 = ofRandom(-1, 1);
    float speedY1 = ofRandom(-1, 1);
    float speedY2 = ofRandom(-1, 1);
    float speedY3 = ofRandom(-1, 1);
    float r = ofRandom(255);
    float g = ofRandom(255);
    float b = ofRandom(255);
    float a = ofRandom(50, 120);
    int color = floor(ofRandom(3)); // 0 or 1 or 2
    float speedColor = ofRandom(-2, 2);
    float speedA = ofRandom(-1, 1);
    
};
#endif
