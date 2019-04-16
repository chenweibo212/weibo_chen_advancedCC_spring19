#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

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
    
    void audioOut( ofSoundBuffer &outBuffer);
    int bufferSize, sampleRate;
    ofSoundStream soundStream;
    
    //setup for frequency modulation
    maxiOsc oscL, oscR, osc1, osc2, mod;
    maxiEnv env;
    double frequency, modulationFrequency, modulationIndex;
    double currentSampleL, currentSampleR, modSample;
    
    //setup for monosynth
    //---->> ofxMaxim monosynth example
    //"https://github.com/firmread/ofxMaxim/blob/master/example_maximilian/14.monosynth.cpp"
    
    maxiOsc timer;
    maxiOsc VCO1,VCO2,LFO1,LFO2;  //voltage contolled oscillator; low frequency oscillation
    maxiFilter VCF;  //voltage-controlled filter
    maxiEnv ADSR;
    int currentCount,lastCount;
    double VCO1out,VCO2out,LFO1out,LFO2out,VCFout,ADSRout;
    
    //---->> ofxMaxim sequencing example
    //"https://github.com/firmread/ofxMaxim/blob/master/example_maximilian/13.Sequencing.cpp"
    
    maxiOsc a,c,d,e,g,h,i,j,squarewave;
    maxiEnvelope b,f;
    maxiDelayline delay;
    maxiFilter myfilter,antia;
    maxiMix mymix;
    double outputs[2];
    double filtered,patch1,patch2,tune,delayed,
    mixed,ramp,noise,pan,more;
    int beat,lastbeat,morebeats;
    double env1[4]={200,0,0,50};
    double env2[6]={10000,0,9000,5,0,5};
    //the melody data
    double melody[14]={600,400,330,650,400,0,400,0,0,425,0,300,0,315};
    //int rhythm1[16]={1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0};

    //setup for getting data
    ofBuffer bufferLatitude;
    ofBuffer bufferLongitude;
    vector <string> issLatitude;
    vector <string> issLongitude;
    vector <float> issLatitude_freq;
    vector <float> issLongitude_freq;

    float frequency_Latitude, frequency_Longitude;
    float targetFrequency_Latitude, targetFrequency_Longitude;
    int noteIndex_Latitude, noteIndex_Longitude;
    
    int time, frame;
};
