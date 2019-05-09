//
//  textRain.hpp
//  GPS_sings
//
//  Created by Weibo Chen on 2019/5/3.
//

#ifndef textRain_hpp
#define textRain_hpp

#include <stdio.h>
#include "ofMain.h"
using namespace std;

class TextRainSymbol{
public:
    float x, y, speed;
    int switchInterval;
    char text;
    string drawText;
    vector <string> textString;
    vector <float> xPos,yPos;
    vector <int> yLength;
    float lineAmount;
    int strLen;
    
    ofTrueTypeFont rainFont;
    float fontSize;
    
    TextRainSymbol();
    TextRainSymbol(float _x, float _y);
    void setToRandomSymbol();
    void render();
    void rain();
    
};

#endif /* textRain_hpp */
