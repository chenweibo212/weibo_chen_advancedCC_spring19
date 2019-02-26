#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    
    mVideo.load("2001ASpaceOdyssey_2.mp4");
    mVideo.setLoopState(OF_LOOP_PALINDROME);
    mVideo.play();
    
    for (int i=0; i<16; i++){
        table[i] = ofRandom(0,255);
    }
    
    ofSetFrameRate(12);
    
    for (int i = 0; i < myTriangles.size(); i++) {
        myTriangles[i].setup();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    mVideo.update();
    
    if (mVideo.isFrameNew()){
        ofPixels pixels = mVideo.getPixels();
        
        int CurrentFrame = mVideo.getCurrentFrame();
        
        for (int y = 0; y < pixels.getHeight(); y++){
            for (int x = 0; x < pixels.getWidth(); x++){
                ofColor col = pixels.getColor(x, y);
                
                col.r = ofMap(mVideo.getCurrentFrame(), 0, 463, 100, table[ col.r/16 ]);
//                col.g = ofMap(mVideo.getCurrentFrame(), 0, 463, 50, table[ col.r/64 ]);
//                col.b = ofMap(mVideo.getCurrentFrame(), 0, 463, 50, table[ col.r/64 ]);
                
                //col.r = table[ col.r/16 ];
                col.g = col.b;
                col.b = col.g;
                
                pixels.setColor(x, y, col);
            }
        }
        
        mImage.setFromPixels(pixels);
    }
    
    for (int i = 0; i < myTriangles.size(); i++) {
        myTriangles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,255,255);
    
    ofSetColor(255,255,255);
    mImage.draw(0,0);
    
    for (int i = 0; i < myTriangles.size(); i++) {
        myTriangles[i].draw();
    }
    
    ofSetColor(255,255,255);
    for(int j=0; j < mImages.size(); j++){
        mImages[j].draw(height[j] + ofRandom(-4, 4), width[j] + ofRandom(-4, 4));
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
        case 'q':
            mVideo.setSpeed(0.09);
            break;
        case 'w':
            mVideo.setSpeed(0.5);
            break;
        case 'e':
            mVideo.setSpeed(1);
            break;
    }
    
    mStrings.push_back(ofToString(key));
    ofImage image;
    string path = "";
    ofDirectory dir(path);
    //populate the directory object
    dir.listDir();
    dir.allowExt("png");
    
    if (key == '1'){
        if (image.load("1.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("1");
        }
        
    }
    
    if (key == '2'){
        if (image.load("2.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("2");
        }
        
    }
    if (key == '3'){
        if (image.load("3.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("3");
        }
        
    }    if (key == '4'){
        if (image.load("4.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("4");
        }
        
    }
    if (key == '5'){
        if (image.load("5.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("5");
        }
        
    }
    if (key == '6'){
        if (image.load("6.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("6");
        }
        
    }
    if (key == '7'){
        if (image.load("7.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("7");
        }
        
    }
    if (key == '8'){
        if (image.load("8.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("8");
        }
        
    }
    if (key == '9'){
        if (image.load("9.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("9");
        }
        
    }
    if (key == '0'){
        if (image.load("10.png")){
            mImages.push_back(image);
            height.push_back(ofRandomHeight());
            width.push_back(ofRandomWidth());
            ofLogNotice("10");
        }
        
    }
    
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
    
   Tri tempTriangle;
   myTriangles.push_back(tempTriangle);
    
    mFloatingNums.push_back(ofRandom(100.0));
    ofLogNotice() << "mFloatingNums has " << mFloatingNums.size()<< endl;
    ofLogNotice() << mFloatingNums.back() << endl;
}

//--------------------------------------------------------------
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
