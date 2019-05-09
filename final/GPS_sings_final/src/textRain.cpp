//
//  textRain.cpp
//  GPS_sings
//
//  Created by Weibo Chen on 2019/5/3.
//

#include "textRain.hpp"

TextRainSymbol::TextRainSymbol(){
}

TextRainSymbol::TextRainSymbol(float _x, float _y){
    x = _x;
    y = _y;
    speed = ofRandom(0.5,1.5);
    switchInterval = floor(ofRandom(1,4));
    lineAmount = ofGetWidth()/fontSize;
    
    fontSize = 20;
    rainFont.load("Roboto-Light.ttf", fontSize, true, true);
    strLen = floor(ofRandom(5,20));
    
    for(int i = 0; i < strLen; i ++){
        yPos.push_back(i*fontSize);
        //ofLogNotice() << yPos[i];
    }
}

void TextRainSymbol::setToRandomSymbol(){
    
    if (ofGetFrameNum() % switchInterval == 0){
        //access single member in a string vector
        char letters[] = "abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+~";
        text = letters[rand() % 39];
        drawText = text;
        //ofLogNotice() << drawText;
    }
}

void TextRainSymbol::render(){
    ofSetColor(100);
    for (int i = 0 ; i <strLen; i++){
        setToRandomSymbol();
        //ofSetColor(100);
        //rainFont.drawString("a", x, yPos[i]);
        ofSetColor(ofRandom(255));
        ofDrawBitmapString(drawText, x, yPos[i]);
        //ofSetColor(ofRandom(255));
        //ofDrawEllipse(x,yPos[i],20,20);
    }
    rain();
    //ofLogNotice() << "rained";
}

void TextRainSymbol::rain(){
    for (int i = 0; i < strLen; i++){
        if (yPos[i] >= ofGetHeight()){
            yPos[i] = 0;
        } else {
            yPos[i] += speed;
        }
    }
}

