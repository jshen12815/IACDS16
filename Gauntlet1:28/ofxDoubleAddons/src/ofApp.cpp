#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    noiseIndex = 0;
    noiseStep = 0.1;
    
    makeLights();
    makeShapes();
    
    rotatingLight = std::make_shared<ofx::Light2D>();
    rotatingLight->setPosition(ofVec3f(2.0f * ofGetWidth() / 2, 2.0f * ofGetHeight() / 3));
    rotatingLight->setViewAngle(ofDegToRad(120));
    

    
    ofSetVerticalSync(true);
    ofBackground(54, 54, 54);
    ofSetFrameRate(60);
    
    int ticksPerBuffer = 4;
    bufferSize = BUFFER_SIZE;
    inChan  = 0;
    outChan = 2;
    sampleRate = SR;
    
    phase1 = phase2 = 0;
    phaseAdder1 = phaseAdder2 = 0.0f;
    phaseAdderTarget1 = phaseAdderTarget2 = 0.0f;
    
    int midiMin = 21;//27.500 hz
    int midiMax = 108;//4186.0 hz
    
    
    for (int i = 0; i < 3; ++i)
    {
        ofx::Light2D::SharedPtr light = std::make_shared<ofx::Light2D>();
        
        ofVec3f position(ofRandomWidth(), ofRandomHeight(), 0);
        ofFloatColor color(ofRandomuf(), ofRandomuf(), ofRandomuf(), 1);
        
        float radius = ofRandom(300, 1000);
        
        float viewAngle = (ofRandom(1) > 0.5) ? TWO_PI : (ofRandom(PI/4, PI/3));
        
        float angle = ofRandom(TWO_PI);
        
        light->setAngle(angle);
        light->setViewAngle(viewAngle);
        light->setPosition(position);
        light->setRadius(radius);
        light->setColor(color);
        light->setPosition(position);
        lightSystem.add(light);
        
        wanderingLights.push_back(light);
    
    }
    
    
    soundStream.setup(this, outChan, inChan, sampleRate, bufferSize, ticksPerBuffer);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    rotatingLight->setAngle(ofWrapRadians(rotatingLight->getAngle() + (PI / 360.0f)));
    
    rotatingLight->setPosition(ofVec3f(ofGetMouseX(),
                                       ofGetMouseY(),
                                       rotatingLight->getPosition().z));


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(0);

}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    
}


void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    while (phase1 > TWO_PI){
        phase1 -= TWO_PI;
    }
    while (phase2 > TWO_PI){
        phase2 -= TWO_PI;
    }
    
    phaseAdder1 = 0.95f * phaseAdder1 + 0.05f * phaseAdderTarget1;
    phaseAdder2 = 0.95f * phaseAdder2 + 0.05f * phaseAdderTarget2;
    
    for (int i = 0; i < bufferSize; i++){
        phase1 += phaseAdder1;
        phase2 += phaseAdder2;
        float sample = sin(phase1) + sin(phase2);
        sample *= 0.5;
        output[i*nChannels    ] = sample;
        output[i*nChannels + 1] = sample;
    }
    
    filterBank.analyze(output);
    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    if (key == 'c')
    {
        lightSystem.clearLights();
        lightSystem.clearShapes();
    }
    else if (key == 'r')
    {
        lightSystem.add(rotatingLight);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    float width = (float)ofGetWidth();
    float widhtPct = (x + y) / (width );
    targetFrequency = ofClamp(4000.0f * widhtPct, 27.5, 4186.0);
    phaseAdderTarget1 = (targetFrequency / (float) sampleRate) * TWO_PI;
    phaseAdderTarget2 = (targetFrequency*1.5 / (float) sampleRate) * TWO_PI;//One Fifth UP

    if (x + y < width) {
        lightSystem.clearLights();
        lightSystem.add(rotatingLight);
    }
    else if (y > width) {
        lightSystem.clearShapes();
        lightSystem.add(rotatingLight);
    }
    else if (y < width) {
        lightSystem.clearShapes();
    }
    else {
    removeLights();

    }
    makeShapes();
    makeLights();
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

void ofApp::makeLights()
{
    for (int i = 0; i < 2; ++i)
    {
        ofx::Light2D::SharedPtr light = std::make_shared<ofx::Light2D>();
        
        ofVec3f position(ofRandomWidth(), ofRandomHeight(), 0);
        ofFloatColor color(ofRandomuf(), ofRandomuf(), ofRandomuf(), 1);
        
        float radius = ofRandom(300, 1000);
        
        light->setPosition(position);
        light->setRadius(radius);
        light->setColor(color);
        
        
        lightSystem.add(light);
    }
}

void ofApp::removeLights()
{
    for (int i = 100; i < 300; ++i)
    {

        ofx::Light2D::SharedPtr light = std::make_shared<ofx::Light2D>();
        
        ofVec3f position(ofRandomWidth(), ofRandomHeight(), 0);
        ofFloatColor color(ofRandomuf(), ofRandomuf(), ofRandomuf(), 1);
        
        float radius = ofRandom(300, 1000);
        
        light->setPosition(position);
        light->setRadius(radius);
        light->setColor(color);
        
        
        lightSystem.remove(light);
    }
}


void ofApp::makeShapes()
{
    for (int i = 0; i < 2; ++i)
    {
        ofx::Shape2D::SharedPtr shape = std::make_shared<ofx::Shape2D>();
        
        ofRectangle rect;
        rect.setFromCenter(ofRandomWidth(),
                           ofRandomHeight(),
                           ofRandom(10, 100),
                           ofRandom(10, 100));
        
        shape->setShape(ofPolyline::fromRectangle(rect));
        lightSystem.add(shape);
    }
}

