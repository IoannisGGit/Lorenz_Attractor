#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ParticleSystem.h"

using namespace glm;

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

		void setupParticleSystem();
		void gridSizeChanged(int &v);
		void displayModeChanged(bool &v);
		void lorenzActivation(bool& v);
		void transfertoLorenz(int& v);

		ParticleSystem myParticleSystem;

		ofxLabel myFpsLabel;
		ofParameter<float> paramAmplitude;
		ofParameter<float> paramTimestep;
		ofParameter<float>paramDamping;
		ofParameter<float>paramRestoreForce;
		ofParameter<int>paramNoiseOctaves;
		ofParameter<float>paramNoiseScale;
		ofParameter<float>paramNoiseRate;
		ofParameter<int> paramGridSizeX;
		ofParameter<int> paramGridSizeY;
		ofParameter<bool> paramShowLines;
		ofParameter<bool> paramShowTriangles;
		ofParameter<bool> activateLorenz;
		ofParameter<int> transfertoLNum;
		ofxButton buttonRestart;
		ofxPanel myGui;

		ofEasyCam myCamera;
		ofMaterial myMeshMaterial;
		ofLight myLight1;
		
		float myPlaneRangeX;
		float myPlaneRangeY;
		float mySphereRadius;
		bool mySphereMode;
		bool show_gui =true;
};
