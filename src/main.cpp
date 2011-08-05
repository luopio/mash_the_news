#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "settings.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	//ofSetupOpenGL(&window, 800, 600, OF_WINDOW);			// <-------- setup the GL context
    ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);

    //ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);

	// game mode works, but the offsets must be counted for the visuals
	// ofSetupOpenGL(&window, 2348,768, OF_GAME_MODE);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
