//
//  Tri.cpp
//  loadvidoe02_colorshift
//
//  Created by Weibo Chen on 2019/2/26.
//

#include <stdio.h>
#include "Tri.h"
Tri::Tri()
{
}
Tri::~Tri()
{
}
void Tri::setup() {
}
void Tri::update() {
    x1 += speedX1;
    x2 += speedX2;
    x3 += speedX3;
    y1 += speedY1;
    y2 += speedY2;
    y3 += speedY3;
    if ((x1 <= -10) || (x1 >= ofGetWidth() + 10)) {
        speedX1 = -speedX1;
    }
    if ((x2 <= -10) || (x2 >= ofGetWidth() + 10)) {
        speedX2 = -speedX2;
    }
    if ((x3 <= -10) || (x3 >= ofGetWidth() + 10)) {
        speedX3 = -speedX3;
    }
    if ((y1 <= -10) || (y1 >= ofGetHeight() + 10)) {
        speedY1 = -speedY1;
    }
    if ((y2 <= -10) || (y2 >= ofGetHeight() + 10)) {
        speedY2 = -speedY2;
    }
    if ((y3 <= -10) || (y3 >= ofGetHeight() + 10)) {
        speedY3 = -speedY3;
    }
    a += speedA;
    if ((a <= 50)||(a >= 120)) {
        speedA = -speedA;
    }
    if (color == 0) {
        r += speedColor;
        if ((r<=0) || (r>=255)) {
            speedColor = -speedColor;
        }
    }
    else if (color == 1) {
        g += speedColor;
        if ((g <= 0) || (g >= 255)) {
            speedColor = -speedColor;
        }
    }
    else {
        b += speedColor;
        if ((b <= 0) || (b >= 255)) {
            speedColor = -speedColor;
        }
    }
}
void Tri::draw() {
    ofFill();
    ofSetColor(r, g, b, a);
    ofDrawTriangle(x1, y1, x2, y2, x3, y3);
}
