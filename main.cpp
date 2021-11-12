#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	
	ofGLWindowSettings settings;
	settings.setGLVersion(4, 3); /// < select your GL Version here
	ofCreateWindow(settings);
	//ofSetupOpenGL(1280, 720, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
