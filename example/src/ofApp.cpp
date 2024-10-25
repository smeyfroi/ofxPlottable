#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
  if (ofRandom(1.0) > 0.93) {
    plottable.addLine(ofRandomWidth(), ofRandomHeight(), ofRandomWidth(), ofRandomHeight(), ofFloatColor(ofRandom(1.0), ofRandom(1.0), ofRandom(1.0)), 60);
  }
  if (ofRandom(1.0) > 0.95) {
    plottable.addCircle(ofRandomWidth(), ofRandomHeight(), ofRandom(30.0), ofFloatColor(ofRandom(1.0), ofRandom(1.0), ofRandom(1.0)), 80);
  }
  if (ofRandom(1.0) > 0.90) {
    plottable.addArc(ofRandomWidth(), ofRandomHeight(), ofRandom(30.0), -1.0 * ofRandom(180.0), ofRandom(180.0), ofFloatColor(ofRandom(1.0), ofRandom(1.0), ofRandom(1.0)), 100);
  }

  plottable.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  plottable.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (plottable.keyPressed(key)) return;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
