#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Set background colour to black
	ofSetBackgroundColor(0);
	ofSetFrameRate(60);
	ofSetFullscreen(true);

	// Set variable values
	myPlaneRangeX = 100.0;
	myPlaneRangeY = 50.0;
	mySphereRadius = 40.0;
	mySphereMode = true;

	// Setup GUI
	myGui.setup();
	myGui.add(myFpsLabel.setup("FPS", ofToString(ofGetFrameRate(), 2)));
	myGui.add(paramAmplitude.set("Amplitude", 2.0, 0.0, 20.0));
	myGui.add(paramTimestep.set("Timestep", 0.1, 0.0, 1.0));
	myGui.add(paramRestoreForce.set("Restore Force", 0.5, 0.0, 1.0));
	myGui.add(paramDamping.set("Damping", 0.1, 0.0, 1.0));
	myGui.add(paramNoiseOctaves.set("Noise Octaves", 1, 1, 16));
	myGui.add(paramNoiseScale.set("Noise Scale", 10.0, 0.0, 60.0));
	myGui.add(paramNoiseRate.set("Noise Rate", 0.1, 0.0, 1.0));
	myGui.add(paramGridSizeX.set("Grid size X", 200, 0, 500));
	myGui.add(paramGridSizeY.set("Grid size Y", 100, 0, 500));
	myGui.add(paramShowLines.set("Show lines", false));
	myGui.add(paramShowTriangles.set("Show triangles", false));
	myGui.add(buttonRestart.setup("Restart"));
	myGui.add(activateLorenz.set("Lorenz Attractor", false));
	myGui.add(transfertoLNum.set("Particles to Attractor", 1, 0, 10));

	// Setup listeners for parameters
	paramGridSizeX.addListener(this, &ofApp::gridSizeChanged);
	paramGridSizeY.addListener(this, &ofApp::gridSizeChanged);
	paramShowLines.addListener(this, &ofApp::displayModeChanged);
	paramShowTriangles.addListener(this, &ofApp::displayModeChanged);
	buttonRestart.addListener(this, &ofApp::setupParticleSystem);
	activateLorenz.addListener(this, &ofApp::lorenzActivation);
	transfertoLNum.addListener(this, &ofApp::transfertoLorenz);

	// Setup the particle system
	setupParticleSystem();

	// Setup EasyCam
	myCamera.setAutoDistance(false);
	myCamera.setPosition(vec3(0.0, 10.0, 100.0));
	myCamera.setTarget(vec3(0.0, 0.0, 0.0));

	// Setup material to use on the particle mesh
	myMeshMaterial.setDiffuseColor(ofFloatColor(0.2, 0.5, 0.7));
	myMeshMaterial.setSpecularColor(ofFloatColor(0.7, 0.7, 0.7));
	myMeshMaterial.setAmbientColor(ofFloatColor(0.1, 0.1, 0.2));
	myMeshMaterial.setShininess(50.0);

	// Setup lights (settings for discrete GPU)
	myLight1.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
	myLight1.setSpecularColor(ofFloatColor(0.0,0.0,0.0));
	myLight1.setPosition(vec3(120.0, 50.0, 120.0));
	myLight1.setAmbientColor(myLight1.getDiffuseColor()*0.5);

}

//--------------------------------------------------------------
void ofApp::update(){
	// Update the particles
	myParticleSystem.update(
		paramAmplitude, paramTimestep, paramRestoreForce,paramDamping, 
		paramNoiseOctaves, paramNoiseScale, paramNoiseRate
	);

	myLight1.setPosition(cos(ofGetElapsedTimef() * .6f) * 100 * 2 + 0.0,
		sin(ofGetElapsedTimef() * .8f) * 100 * 2 + 0.0,
		-cos(ofGetElapsedTimef() * .8f) * 100 * 2 + 0.0);
	
	// Update the frames per second label in the GUI
	myFpsLabel = ofToString(ofGetFrameRate(), 2);
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Start drawing objects in 3D space
	ofEnableDepthTest();
	myLight1.enable();
	myCamera.begin();

	// Switch on the lights
	ofEnableLighting();
	
	// Draw the particles
	myMeshMaterial.begin();
	ofRotateY(ofGetElapsedTimef()*10);
	myParticleSystem.draw();
	myMeshMaterial.end();
	
	// Switch off lighting
	ofDisableLighting();

	// Finish drawing objects in 3D space
	myCamera.end();
	ofDisableDepthTest();

	// Draw the GUI elements
	if(show_gui)myGui.draw();
}

//--------------------------------------------------------------
void ofApp::setupParticleSystem() {
	ofPrimitiveMode curDisplayMode;
	if (paramShowTriangles) {
		curDisplayMode = OF_PRIMITIVE_TRIANGLES;
	}
	else if (paramShowLines) {
		curDisplayMode = OF_PRIMITIVE_LINES;
	}
	else {
		curDisplayMode = OF_PRIMITIVE_POINTS;
	}

	// Call the appropriate setup function depending whether we're
	// displaying as a plane or a sphere
	if (mySphereMode) {
		myParticleSystem.setupSphere(paramGridSizeX, paramGridSizeY, mySphereRadius, curDisplayMode);
	}
	else {
		myParticleSystem.setupPlane(paramGridSizeX, paramGridSizeY, myPlaneRangeX, myPlaneRangeY, curDisplayMode);
	}
}

//--------------------------------------------------------------
void ofApp::gridSizeChanged(int &v) {
	// Simply call setupParticleSystem
	setupParticleSystem();
}

//--------------------------------------------------------------
void ofApp::displayModeChanged(bool &v) {
	// Simply call setupParticleSystem
	setupParticleSystem();
}

void ofApp::lorenzActivation(bool& v) {
	myParticleSystem.activateLorenz(v);
}

void ofApp::transfertoLorenz(int& num) {
	myParticleSystem.setTransferNum(num);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g') {
		show_gui = !show_gui;
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
