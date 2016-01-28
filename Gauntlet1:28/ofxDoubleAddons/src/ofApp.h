#pragma once

#include "ofMain.h"
#include "LightSystem2D.h"
#include "ofxFilterbank.h"

#define BANDWITH  1.0
#define BUFFER_SIZE 512
#define LIN2dB(x) (double)(20. * log10(x))
#define SR 44100


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
    
        void makeLights();
        void removeLights();
        void makeShapes();
    
        float noiseIndex;
        float noiseStep;
    
        ofx::Light2D::List wanderingLights;
    
        ofx::Light2D::SharedPtr rotatingLight;
    
        ofx::LightSystem2D lightSystem;
    
        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut(float * input, int bufferSize, int nChannels);
    
    
        ofSoundStream soundStream;
        ofxFilterbank filterBank;
    
        int	sampleRate;
        int bufferSize;
        int inChan;
        int outChan;
    
        float phase1, phase2;
        float phaseAdder1, phaseAdder2;
        float phaseAdderTarget1, phaseAdderTarget2;
        float targetFrequency;

    

		
};
