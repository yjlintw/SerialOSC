#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    serialConnection.connect();
    sender.setup("127.0.0.1", 5000);
}

//--------------------------------------------------------------
void ofApp::update(){
    serialConnection.getMsgs();
    float ax = ofToFloat(serialConnection.getValue("ax"));
    float ay = ofToFloat(serialConnection.getValue("ay"));
    float az = ofToFloat(serialConnection.getValue("az"));

    ofxOscMessage m;
    m.setAddress("acc");
    m.addFloatArg(ax);
    m.addFloatArg(ay);
    m.addFloatArg(az);
    sender.sendMessage(m, false);
    
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a' || key == 'A') {
        ofxOscMessage m;
        m.setAddress("/test");
        m.addFloatArg(3.5f);
        m.addFloatArg(1.65f);
        m.addFloatArg(0.88f);
        sender.sendMessage(m, false);
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
