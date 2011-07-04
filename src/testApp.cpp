#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    box2d.init();
    box2d.setGravity(0, 1);
    // box2d.createFloor();
    box2d.createBounds();
    box2d.checkBounds(true);
    box2d.setFPS(30.0);

    screen.setup();
}

//--------------------------------------------------------------
void testApp::update(){
    screen.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    screen.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

