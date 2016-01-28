/*
* Sound Light Movement Thing
* Jessica Shen
* jshen1
* 51-482 Interactive Art and Computational Design
* January 28, 2016
*
* ofxFilterBank
* https://github.com/leozimmerman/ofxFilterbank
*
* ofxLight2D
* https://github.com/bakercp/ofxLight2D
*
*/



#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
