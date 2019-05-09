#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255);
    ofSetCircleResolution(64);
    
    //audio setup
    sampleRate = 44100;
    bufferSize = 1024;
    ofSoundStreamSetup(2,0,this,sampleRate,bufferSize,4);
    ofSoundStreamStop();
    
    //make a timer -- GPS
    startTimeGPS = ofGetElapsedTimeMillis();
    endTimeGPS = 1600;
    
    //make a timer -- DAYS
    startTimeDAY = ofGetElapsedTimeMillis();
    endTimeDAY = 2000;
    
    //decided step total amount
    stepAmountGPS = 29;
    stepAmountDAY = 8;
    
    //set position of the sequencer  -- same for both layer
    sequencerX = 0;
    sequencerY = 0;
    sequencerWidth = ofGetWidth();
    sequencerHeight = ofGetHeight();
    gap = 0.1;
    
    //setup step size -- GPS
    stepSizeWGPS = ofGetWidth()/stepAmountGPS;
    stepSizeHGPS = ofGetHeight()/stepAmountGPS;
    
    //setup step size -- DAY
    stepSizeWDAY = ofGetWidth()/stepAmountDAY;
    stepSizeHDAY = ofGetHeight()/stepAmountDAY;

    //populate sequencer -- GPS
    for (unsigned i = 0; i < 29; i++){
        stringstream s;
        s << "/Users/BEAR/Desktop/spring2019/advancedcc/code/of_v0.10.1_osx_release/apps/final/API_GPS_Satellite/bin/data/gps_in_words/" << i << ".wav";
        //populate seqCollection with samples and other pre-decalared perimeters
        seqsGPS.push_back(unique_ptr<Sequencer>(new Sequencer(sequencerX,sequencerY + i * (stepSizeHGPS + gap), sequencerWidth, sequencerHeight, s.str(), stepAmountGPS, gap)));
    }
    
    //populate sequencer -- DAY
    for (unsigned i = 0; i < 8; i++){
        stringstream s;
        s << "/Users/BEAR/Desktop/spring2019/advancedcc/code/of_v0.10.1_osx_release/apps/final/API_GPS_Satellite/bin/data/days/" << i << ".wav";
        //populate seqCollection with samples and other pre-decalared perimeters
        seqsDAY.push_back(unique_ptr<Sequencer>(new Sequencer(sequencerX,sequencerY + i * (stepSizeHDAY + gap), sequencerWidth, sequencerHeight, s.str(), stepAmountDAY, gap)));
    }
    
    //current playhead in samples
    currentGPS = 0.f;
    currentDAY = 0.f;
    
    //decide display window size
    ofSetWindowShape((stepAmountGPS + 1) * (stepSizeWGPS + gap), seqsGPS.size() * (stepSizeHGPS + gap));
    
    // Reading all GPS Satellites ID from local file
    bufferGPS_SATELLITES_ID = ofBufferFromFile("GPS_SATELLITES_ID.txt");
    for (auto lineX : bufferGPS_SATELLITES_ID.getLines()){
        GPS_SATELLITES_ID = ofSplitString(lineX, ";");
        GPS_SATELLITES_ID.push_back(lineX); //need to remove line break before each string
    }
    
    for (int i = 0; i < GPS_SATELLITES_ID.size()-2; i++){
        //total 31 satellites
        //get the location of all satelites in next 1 second from my current view point(41.702, -76.014)
        API_URL.push_back("https://www.n2yo.com/rest/v1/satellite/positions/" + GPS_SATELLITES_ID[i] + "/40.714/-74.005/0/1/&apiKey=" + API_KEY);
    }
    
    // on/off button
//    circleButton_getData.set(ofGetWidth()/3,(ofGetHeight()/3)*2);
//    circleButton_play.set((ofGetWidth()/3)*2,(ofGetHeight()/3)*2);
//    radius = 40;
    
    bRectButton_getData = false;
    bRectButton_play = false;
    
    How.load("how.wav");
    What.load("what.wav");
    
//    pos = ofVec2f(ofGetWidth()* 1.5/5,ofGetHeight()* 1.5/5);
//    size = ofVec2f(ofGetWidth() * 2/5,ofGetHeight()* 2/5);
    pos = ofVec2f(0,0);
    size = ofVec2f(ofGetWidth(),ofGetHeight());
    
    setButton();
    buttonFontSizeL = size.x/30;   //50
    buttonFontSizeR = size.x/30;   //25
    fontButtonL.load("Roboto-Light.ttf", buttonFontSizeL, true, true);
    fontButtonR.load("Roboto-Light.ttf", buttonFontSizeR, true, true);
    fontButtonR_2.load("Roboto-Light.ttf", size.x/35, true, true);
    buttonLText1 = "go ahead";
    buttonLText2 = "that is enough";
    buttonRText1 = "button under maintenance";
    buttonRText2 = "give me a break";
    buttonRText3 = "you may resume";
    
    //textRain setup
    totalLine = ofGetWidth()/20;
    
    for (int i = 0; i < totalLine; i++){
        xPosition.push_back(i*20);
        ofLogNotice() << xPosition[i];
    }
    
    for (int i = 0; i <totalLine; i++){
        drawText.push_back(TextRainSymbol(xPosition[i],ofRandom(ofGetWidth())));
        
        ofLogNotice() << "done.";
    }
    
    angle = 0.05;
    constantX = (ofGetScreenWidth()+size.x)/2;
    constantY = (ofGetScreenHeight()+size.y)/2;
    scalar = 100;
    speed = 0.005;
}

//--------------------------------------------------------------
void ofApp::update(){
    currentTimeGPS = ofGetElapsedTimeMillis() - startTimeGPS;
    currentTimeDAY = ofGetElapsedTimeMillis() - startTimeDAY;
    
    if (currentTimeGPS >= endTimeGPS){
        currentGPS = ++currentGPS % stepAmountGPS;
        
        for (seqCollection::iterator it = seqsGPS.begin(); it != seqsGPS.end(); it++){
            //seqCollection is a vector of pointer, need to de-reference it twice
            (*it)->rewind();
        }
        startTimeGPS = ofGetElapsedTimeMillis();
    }
    
    if (currentTimeDAY >= endTimeDAY){
        currentDAY = ++currentDAY % stepAmountDAY;
        
        for (seqCollection::iterator it = seqsDAY.begin(); it != seqsDAY.end(); it++){
            //seqCollection is a vector of pointer, need to de-reference it twice
            (*it)->rewind();
        }
        startTimeDAY = ofGetElapsedTimeMillis();
    }
    
    //textRain
    for (int i = 0; i < totalLine; i++){
        drawText[i].setToRandomSymbol();
    }
    
    float windowX = constantX + sin(angle)*scalar;
    float windowY = constantY + cos(angle)*scalar;
    
//    ofSetWindowPosition( (ofGetScreenWidth()-size.x)/2+sin(ofGetElapsedTimef())*50,(ofGetScreenHeight()-size.y)/2+sin(ofGetElapsedTimef())*50);
    angle = angle + speed;
    ofLogNotice() << angle;
    ofSetWindowPosition(windowX,windowY);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(15);
    ofSetColor(0);
    
    presetStepsGPS();
    presetStepsDAY();
    
    //textRain
    for (int i = 0; i < totalLine; i++){
        drawText[i].render();
    }
    
    popNotification(pos, size);
    
    
    if (bRectButton_getData){
        ofSetColor(120);
        drawButtonL();
        ofSetColor(0);
        fontButtonL.drawString(buttonLText2, buttonL.x + buttonL.width/4, buttonL.y + buttonL.height/1.6);
    } else {
        ofSetColor(150);
        drawButtonL();
        ofSetColor(0);
        fontButtonL.drawString(buttonLText1, buttonL.x + buttonL.width/3, buttonL.y + buttonL.height/1.6);
    }
    
    ofSetColor(120);
    drawButtonR();
    ofSetColor(0);
    fontButtonR_2.drawString(buttonRText1, buttonR.x + buttonR.width/10, buttonR.y + buttonR.height/1.6);
    
    if (isPlay){
        if (bRectButton_play){
        ofSetColor(80);
        drawButtonR();
        ofSetColor(0);
        fontButtonR.drawString(buttonRText3, buttonR.x + buttonR.width/5-5, buttonR.y + buttonR.height/1.6);

        } else {
        ofSetColor(120);
        drawButtonR();
        ofSetColor(0);
        fontButtonR.drawString(buttonRText2, buttonR.x + buttonR.width/5, buttonR.y + buttonR.height/1.6);
        }
    }
    
    if (gotData){
        for (int i = 0; i < locationX.size(); i++){
            //assign on position to GPS sequencer
              unsigned xPos = floor((float)locationX[i] / ofGetWidth()*stepAmountGPS);
              unsigned yPos = floor((float)locationY[i] / (stepSizeHGPS + gap));
              unsigned xPresetGPS = floor((float)preX[i] / ofGetWidth()*stepAmountGPS);
              unsigned yPresetGPS = floor((float)preY[i] / (stepSizeHGPS  + gap));
            
           //assign pressed step to the sequencer
           if (setStepsGPS[i]) {
              //set on steps --- GPS
              seqsGPS[yPresetGPS]->steps[xPresetGPS].pressed();
              seqsGPS[yPos]->steps[xPos].pressed();
              setStepsGPS[i] = false;
           }
            ofSetColor(100);
            //ofDrawEllipse(locationX[i], locationY[i], 40, 40);
        }
        for (int i = 0; i < setStepsDAY.size(); i++){
         //assign on position to DAY sequencer
            unsigned xPreset = floor((float)preXDAY[i] / ofGetWidth() * stepAmountDAY);
            unsigned yPreset = floor((float)preYDAY[i] / (stepSizeHDAY  + gap));
         //set on steps --- DAY (preset)
            if (setStepsDAY[i]) {
                //set on steps --- GPS
                seqsDAY[yPreset]->steps[xPreset].pressed();
                setStepsDAY[i] = false;
            }
        }
    }
    
    //render each sequence
    for (seqCollection::iterator it = seqsGPS.begin(); it != seqsGPS.end(); it++){
        (*it)->render(currentGPS);
    }
    for (seqCollection::iterator it = seqsDAY.begin(); it != seqsDAY.end(); it++){
        (*it)->render(currentDAY);
    }
    
    //button
//    if (bCircleButton_getData){
//            ofSetColor(10);
//            ofDrawCircle(circleButton_getData, radius);
//    }else{
//            ofSetColor(100);
//            ofDrawCircle(circleButton_getData, radius);
//    }
//
//    if (isPlay){
//      if (bCircleButton_play){
//        ofSetColor(10);
//        ofDrawCircle(circleButton_play, radius);
//      }else{
//        ofSetColor(100);
//        ofDrawCircle(circleButton_play, radius);
//     }
//    }
    
    //
    ofSetColor(80);
    ofDrawRectangle(pos.x,pos.y + (3*size.y)/4,size.x,1);
    ofDrawRectangle(pos.x + size.x/2, pos.y + (3*size.y)/4, 1, size.y/4);
}

//--------------------------------------------------------------
void ofApp::getSatelliteData(){
     //parsing JSON
    for (int i = 0; i < API_URL.size(); i++){
        parsingSuccessful.push_back(json[i].open(API_URL[i]));
    }
    
    for (int i = 0; i < parsingSuccessful.size(); i++){
        RAW_JSON.push_back(json[i].getRawString(true));
    }
    
    for (int j = 0; j < RAW_JSON.size(); j++){
        for (Json::ArrayIndex i = 0; i < json[j]["positions"].size(); ++i)
        {
            std::string sataltitude  = json[j]["positions"][i]["sataltitude"].asString();
            std::string satlatitude = json[j]["positions"][i]["satlatitude"].asString();
            std::string satlongitude   = json[j]["positions"][i]["satlongitude"].asString();
            std::string index = ofToString(j);
            std::string text = index + "satid: "  + GPS_SATELLITES_ID[j] + "sataltitude: " + sataltitude + " ; " + "satlatitude: " + satlatitude + " ; " + "satlongitude: " + satlongitude;
            
            float x = ofMap(ofToFloat(satlongitude), -180,180,20,ofGetWidth()-20);
            float y = ofMap(ofToFloat(satlatitude),-60,60, ofGetHeight()-20, 20);
            locationX.push_back(x);
            locationY.push_back(y);
        }
    }
}

//--------------------------------------------------------------

void ofApp::clearSatelliteData(){
    parsingSuccessful.clear();
    RAW_JSON.clear();
    locationX.clear();
    locationY.clear();
}

//--------------------------------------------------------------

void ofApp::presetStepsGPS(){
    for (int i = 0; i < stepAmountGPS; i++){
            preX.push_back(2 + i * (ofGetWidth()/totalSampleGPS));
            preY.push_back(2 + i * (ofGetHeight()/totalSampleGPS));
    }
}

//--------------------------------------------------------------

void ofApp::presetStepsDAY(){
    for (int i = 0; i < stepAmountDAY; i++){
        preXDAY.push_back(10 + i * (ofGetWidth()/totalSampleDAY));
        preYDAY.push_back(2 + i * (ofGetHeight()/totalSampleDAY));
    }
}

//--------------------------------------------------------------

void ofApp::audioOut(ofSoundBuffer &outBuffer){
    for (int i = 0; i < bufferSize; i++){
        currentSampleGPS = 0;
        currentSampleDAY = 0;
        
        for (seqCollection::iterator it = seqsGPS.begin(); it != seqsGPS.end(); it++){
            if ((*it)->steps[currentGPS].on == true){
                currentSampleGPS += (*it)->sample.play(1) / seqsGPS.size();
            }
        }
        for (seqCollection::iterator it = seqsDAY.begin(); it != seqsDAY.end(); it++){
            if ((*it)->steps[currentDAY].on == true){
                currentSampleDAY += (*it)->sample.play(1) / seqsDAY.size();
            }
        }
        
        mixGPS.stereo(currentSampleGPS, outputsGPS, 1);
        mixDAY.stereo(currentSampleDAY, outputsDAY, 0);
        
        outBuffer[i * outBuffer.getNumChannels()] = outputsGPS[0] + outputsDAY[0] * 0.2;
        outBuffer[i * outBuffer.getNumChannels()+1] = outputsGPS[1] + outputsDAY[1] * 0.5;
    }
}

//--------------------------------------------------------------
void ofApp::buttonAClicked(){
    if (bRectButton_getData){
        ofLogNotice() << "on";
        getSatelliteData();
        gotData = true;
        for (int i = 0; i < 29; i++){
            setStepsGPS.push_back(true);
        }
        for (int i = 0; i < 8; i++){
            setStepsDAY.push_back(true);
        }
        ofSoundStreamStart();
        
        soundPlayerSetup();
        How.play();
        What.play();
        bRectButton_play = false;
        isPlay = true;
    } else if (!bRectButton_getData){
        ofLogNotice() << "off";
        clearSatelliteData();
        gotData = false;
        vectorCleared = true;
        ofLogNotice() << "cleared";
        ofSoundStreamStop();
        How.stop();
        What.stop();
        isPlay = false;
    }
}

//--------------------------------------------------------------
void ofApp::buttonBClicked(){
    if (bRectButton_play){
        ofSoundStreamStop();
        How.setPaused(true);
        What.setPaused(true);
        ofLogNotice() << "stopped";
    } else {
        ofSoundStreamStart();
        How.setPaused(false);
        What.setPaused(false);
        ofLogNotice() << "started";
    }
}

void ofApp::soundPlayerSetup(){
    How.setVolume(0.01f);
    How.setPan(0.5);
    What.setVolume(0.02f);
    What.setPan(0.5);
}
void ofApp::popNotification(ofVec2f posVec, ofVec2f sizeVec){
    pos = posVec;
    size = sizeVec;
    xB = posVec.x;
    yB = posVec.y;
    //    w = (floor(ofRandom(3, 15)))*50;
    //    h = (w/16)*9;
    w = sizeVec.x;
    h = sizeVec.y;
    xL = pos.x;
    yL = yR = pos.y + (3*h)/4;
    xR = pos.x + w/2;
    fontSize1 = w/25;
    fontSize2 = w/50;
    rectBG.set(xB,yB,w,h);
    
    //ofSetColor(ofLerp(0,255,50));
//    for (int i = 0; i < 10; i++){
//        ofSetColor(255-i*5,80-i*5);
//        ofDrawRectRounded((xB-5)+i/2,(yB-5)+i/2, w+10-i, h+10-i,30);
//    }
    ofSetColor(255,200);
    ofDrawRectRounded(rectBG,10);
    font1.load("Roboto-Light.ttf", fontSize1, true, true);
    font2.load("Roboto-Light.ttf", fontSize2, true, true);
    

    
    string Text1 = "allow maps to access your location";
    string Text2 = "if you don’t mind it just takes a second or might be a while an hour a day a month a year not sure let me think about it as i am arranging elements in time and space when what who how why now staring gazing looking watching viewing seeing here there lots of time too much time all the time";
    
    //i hope this finds you well
    
    notificationText1 = wrapString(font1, Text1, w);
    notificationText2 = wrapString(font2, Text2, (w*4)/5);
    ofSetColor(10);
    font1.drawString(notificationText1, xB + w/10, yB + h/4);
    ofSetColor(40);
    font2.drawString(notificationText2, xB + w/10, yB + h/3+20);
};

void ofApp::setButton(){
    buttonL.set(pos.x,pos.y + (3*size.y)/4,size.x/2,size.y/4);
    buttonR.set(pos.x + size.x/2,pos.y + (3*size.y)/4,size.x/2,size.y/4);
}

void ofApp::drawButtonL(){
    ofDrawRectRounded(buttonL,0,0,0,10);
}

void ofApp::drawButtonR(){
    ofDrawRectRounded(buttonR,0,0,10,0);
}

string ofApp::wrapString(ofTrueTypeFont font, string text, int width) {
    
    string typeWrapped = "";
    string tempString = "";
    vector <string> words = ofSplitString(text, " ");
    
    for(int i=0; i<words.size(); i++) {
        
        string wrd = words[i];
        
        // if we aren't on the first word, add a space
        if (i > 0) {
            tempString += " ";
        }
        tempString += wrd;
        
        int stringwidth = font.stringWidth(tempString);
        
        if(stringwidth >= width) {
            typeWrapped += "\n";
            tempString = wrd;        // make sure we're including the extra word on the next line
        } else if (i > 0) {
            // if we aren't on the first word, add a space
            typeWrapped += " ";
        }
        
        typeWrapped += wrd;
    }
    
    return typeWrapped;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------

void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    if (circleButton_getData.distance(ofPoint(x,y)) < radius) {
//        bCircleButton_getData = !bCircleButton_getData;
//        //buttonAClicked();
//    }
//
//    if (isPlay){
//        if (circleButton_play.distance(ofPoint(x,y)) < radius){
//            bCircleButton_play = !bCircleButton_play;
//            //buttonBClicked();
//        }
//    } else {
//        bCircleButton_play = false;
//    }
    
    if (buttonL.inside(x, y)){
        bRectButton_getData = !bRectButton_getData;
        buttonAClicked();
    }
    if (isPlay){
    if (buttonR.inside(x, y)){
        bRectButton_play = !bRectButton_play;
        buttonBClicked();
    }
    }
    
    
}

void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
