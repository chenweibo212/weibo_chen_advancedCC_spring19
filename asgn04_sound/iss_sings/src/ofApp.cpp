#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sampleRate = 44100;
    bufferSize = 512;

    ADSR.setAttack(1000);
    ADSR.setDecay(1);
    ADSR.setSustain(1);
    ADSR.setRelease(1000);
    
    env.setAttack(0);
    env.setDecay(200);
    env.setSustain(0.2);
    env.setRelease(2000);
    env.trigger = 1;
    
    b.amplitude=env1[0];//starting value for envelope b
    f.amplitude=env2[0];//same for f
    
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);

    bufferLatitude = ofBufferFromFile("iss1_x.txt");
    bufferLongitude = ofBufferFromFile("iss1_y.txt");
    
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    
//ISS location data March 30 14:32 - 16:00
//"http://api.open-notify.org/iss-now.json"
    
    for (auto lineX : bufferLatitude.getLines()){
        issLatitude.push_back(lineX);
        issLatitude = ofSplitString(lineX, ",");
    }
    
    for (int i = 0; i < issLatitude.size(); i++){
        float dataX = ofToFloat(issLatitude[i]);
        float datatoFreq = roundf(ofMap(dataX, -50, 50, 100, 300, true));
        issLatitude_freq.push_back(datatoFreq);
    }
    
    for (auto lineY : bufferLongitude.getLines()){
        issLongitude.push_back(lineY);
        issLongitude = ofSplitString(lineY, ",");
    }
    
    for (int i = 0; i < issLongitude.size(); i++){
        float dataX = ofToFloat(issLongitude[i]);
        float datatoFreq = roundf(ofMap(dataX, -180, 180, 200, 400, true));
        issLongitude_freq.push_back(datatoFreq);
    }
    
      frame = ofGetFrameNum();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
}
//--------------------------------------------------------------
void ofApp::audioOut( ofSoundBuffer &outBuffer){
    //setup basic frequency data
    targetFrequency_Latitude = issLatitude_freq[noteIndex_Latitude];
    frequency_Latitude = ofLerp(frequency_Latitude, targetFrequency_Latitude, 0.9);
    targetFrequency_Longitude = issLongitude_freq[noteIndex_Longitude];
    frequency_Longitude = ofLerp(frequency_Longitude, targetFrequency_Longitude, 0.9);
    
    //for frequency modulation
    //this sets up a metronome that ticks every 2 seconds
    currentCount=(int)timer.phasor(0.1);
    
    currentSampleL = oscL.sinewave(targetFrequency_Latitude);
    currentSampleR = oscR.sinewave(targetFrequency_Longitude);
    
    modulationFrequency = ofMap(currentSampleL, -1, 1, 0, 10);
    modulationIndex = ofMap(currentSampleR, -1, 1, 100, 200);
    
    //for monosynth
    if (lastCount!=currentCount) {
        ADSR.trigger=1;
        lastCount=0;//set lastCount to 0
    }
    
    //for melody sequence
    beat=((int) c.phasor(8));
    morebeats=((int) e.phasor(0.5,0,16));
    patch1=b.line(4,env1);
    patch2=f.line(6,env2);
    tune=g.sinewave(melody[morebeats]*0.25);
    if (lastbeat!=beat) {//this is a nice sample and hold routine for the kick drum
        f.trigger(0, env2[0]);//it runs off the hi hat.
        
        
        if (rhythm1[morebeats]==1) {
            b.trigger(0, env1[0]);//and gets played when it's time.
        }
    }
    lastbeat=beat;
    
    for (int q = 0 ; q<bufferSize; q++) {
    //monosynth
    ADSRout=ADSR.adsr(1.0,ADSR.trigger);
    
    LFO1out=LFO1.sinebuf(0.2);//this lfo is a sinewave at 0.2 hz
    
    VCO1out=VCO1.sinewave(frequency_Latitude);
    VCO2out=VCO2.sinewave(frequency_Longitude+LFO1out);
    //stick the VCO's into the VCF, using the ADSR as the filter cutoff
    VCFout=VCF.lores((VCO1out+VCO2out)*0.5, ADSRout*10000, 10);
    //finally add the ADSR as an amplitude modulator
    double monoSound=VCFout*ADSRout;
    ADSR.trigger=1;
    
    //frequency modulation
    double modFreqSample = osc1.sinewave(targetFrequency_Latitude + env.adsr(mod.sinewave(modulationFrequency), env.trigger) * modulationIndex);
    
    double sinSample = osc2.sinewave(targetFrequency_Longitude);
    
    modSample = modFreqSample + sinSample * 0.3;
    modSample *= 0.8;
    modSample = ofClamp( modSample, -1.0, 1.0);
    
    //sequencing
    ramp=i.phasor(0.5,1,2048);//create a basic ramp
    pan=j.phasor(0.25);//some panning from a phasor (object is equal power)
    
    delayed=delay.dl(tune, ramp, 0.9)*0.125;
    mixed=((a.sinewave(patch1)*0.5)+((d.saw(patch2))*0.125)+(delayed*0.3)*0.5);
    
    noise=i.noise()*0.25;
    
    more=squarewave.pulse(melody[morebeats],pan)*0.05;
    
    mymix.stereo(more+mixed+delayed, outputs, 1-pan);
    
    outBuffer[q * outBuffer.getNumChannels()] = outputs[0] * 0.5 + monoSound * 0.8;
    outBuffer[q * outBuffer.getNumChannels()+1] = outputs[1] * 0.5 + modSample;
    }
    
    if (frame % 60 == 0 || frame == 1){
        noteIndex_Latitude++;
        noteIndex_Longitude++;
        if (noteIndex_Latitude > issLatitude_freq.size()){
            noteIndex_Latitude = 0;
        }
        if (noteIndex_Longitude > issLongitude_freq.size()){
            noteIndex_Longitude = 0;
        }
    }
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
