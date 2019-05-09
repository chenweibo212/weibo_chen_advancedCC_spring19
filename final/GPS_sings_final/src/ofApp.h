#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "textRain.hpp"

//construct steps
struct Step {
    float x,y,sizeW,sizeH;
    bool on;
    
    void render(bool _this){
        if (_this) {                        //playhead
            ofSetColor(50);
            //ofDrawRectangle(x,y,1,sizeH);
        } else if (on) {                    //note is on
            ofSetColor(200);
        } else {
            ofSetColor(255);
        }
        
        //control on/off with an outside mousepressed class;
        //ofDrawRectangle(x,y,sizeW,sizeH);
    }
    
    void pressed(){                        //whether a square is being pressed
        on = !on;
    }
};

//construct sequencer
struct Sequencer {
    unsigned stepAmount;
    float x, y, w, height, h;
    vector<Step> steps;
    ofxMaxiSample sample;   //bitspersample = 16;
    
    Sequencer(float _x, float _y, float _w, float _h, string _sampleName, unsigned _stepAmount, int _gap) {
        
        stepAmount = _stepAmount;
        sample.load(ofToDataPath(_sampleName));
        x = _x;
        y = _y;
        w = _w;
        height = _h;
        h = _w/stepAmount;
        
        //loop through and push back steps into vector
        for (int i = 0; i < stepAmount; i++){
            Step temp;
            //set step places
            temp.sizeW = _w/stepAmount;
            temp.sizeH = height/stepAmount;
            temp.x = i + i * (temp.sizeW + _gap);
            temp.y = y;
            temp.on = false;
            steps.push_back (temp);
        }
    }
    
    void rewind(){
        sample.setPosition(0);
    }
    
    void render(unsigned _current){
        for (int i = 0; i < stepAmount; i++){
            if (i == _current) {
                steps[i].render(true);
            } else {
                steps[i].render(false);
            }
        }
    }
};

//unique pointer of sequencers
typedef vector<unique_ptr<Sequencer>> seqCollection;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
    //step sequencer & audio setups
    seqCollection seqsGPS, seqsDAY;
    
    void audioOut(ofSoundBuffer &outBuffer);
    unsigned bufferSize, sampleRate;
    
    unsigned startTimeGPS, endTimeGPS, currentTimeGPS, currentGPS, stepAmountGPS;
    unsigned startTimeDAY, endTimeDAY, currentTimeDAY, currentDAY, stepAmountDAY;
    unsigned gap;
    
    float sequencerX, sequencerY, sequencerWidth,sequencerHeight;
    
    float stepSizeWGPS, stepSizeHGPS, sequencerXGPS, sequencerYGPS;
    float stepSizeWDAY, stepSizeHDAY, sequencerXDAY, sequencerYDAY;
    
    double currentSampleGPS, currentSampleDAY;
    
    double outputsGPS[2], outputsDAY[2];

    
    maxiMix mixGPS,mixDAY;
    
    //some preset steps
    void presetStepsGPS();
    vector <float> preX;
    vector <float> preY;
    int totalSampleGPS = 29;
    
    void presetStepsDAY();
    vector <float> preXDAY;
    vector <float> preYDAY;
    int totalSampleDAY = 8;
    
    //get satellite data
        void getSatelliteData();
        void clearSatelliteData();
		
        ofxJSONElement *json = new ofxJSONElement[31];
        ofxJSONElement json1;
        string API_KEY = "C4VE3X-ZDRPGN-44N2AV-3ZOJ";
        vector <std::string> API_URL;
        vector <std::string> RAW_JSON;
        vector <bool> parsingSuccessful;
    
        ofBuffer bufferGPS_SATELLITES_ID;
        vector <string> GPS_SATELLITES_ID;
    
        bool gotData = false;
        bool vectorCleared = false;
        vector <bool> setStepsGPS;
        vector <float> locationX;
        vector <float> locationY;
        vector <bool> setStepsDAY;
    
        bool isPlay;
    
    //button
    ofPoint circleButton_getData, circleButton_play;
    bool bCircleButton_getData, bCircleButton_play;
    int radius;
    
    void buttonAClicked();
    void buttonBClicked();
    
    //unfinished part
    bool showSteps = true;
    
    ofSoundPlayer  How, What;
    void soundPlayerSetup();
    
    void popNotification(ofVec2f posVec, ofVec2f sizeVec);
    void setButton();
    void drawButtonL();
    void drawButtonR();
    bool bRectButton_getData, bRectButton_play;
    ofTrueTypeFont fontButtonL,fontButtonR,fontButtonR_2;
    string buttonLText1, buttonLText2, buttonRText1, buttonRText2, buttonRText3;
    float buttonFontSizeL,buttonFontSizeR;
    
    
    //notification box BG
    string wrapString(ofTrueTypeFont font, string text, int width);
    string notificationText1, notificationText2;
    vector <string> randomWords;
    ofTrueTypeFont font1, font2;
    float fontSize1, fontSize2, textX, textY;
    ofVec2f pos, size;
    float xB, xL, xR, w;        // position
    float yB, yL, yR, h;
    ofRectangle buttonL,buttonR,rectBG,rectBG2;
    
    
    //RainTogether raining;
    TextRainSymbol drawSingleText;
    vector <TextRainSymbol> drawText;
    float totalLine;
    vector <float> xPosition;
    
    float angle;
    int constantX, constantY;
    int scalar;
    float speed;
};
