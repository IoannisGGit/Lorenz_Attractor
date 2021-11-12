#pragma once

#include "ofMain.h"
#include "Particle.h"

using namespace glm;

class ParticleSystem {
public:
	void setupPlane(int gridSizeX, int gridSizeY, float planeRangeX, float planeRangeY, ofPrimitiveMode displayMode);
	void setupSphere(int gridSizeX, int gridSizeY, float sphereRadius, ofPrimitiveMode displayMode);
	void update(
		float amplitude, float timestep, float restoreForce, float damping, 
		int noiseOctaves, float noiseScale, float noiseRate);
	void draw();
	vec3 lorenzAttractor(vec3 pos);
	void activateLorenz(bool active);
	void setTransferNum(int num);

private:
	void transferParticles(int time, int numParticles);
	void swapParticles(int index);
	int transferTime = 1;
	int transferNum = 0;
	int counter;
	int transferIndex =0;
	int getParticleIndex(int x, int y);

	vec3 center = vec3(0.0, 0.0, 0.0);
	vec3 offset = vec3(0.0, 0.0, 0.0);
	vector<Particle> myParticles;
	vector<Particle>myParticles2;
	ofMesh myMesh;
	ofPrimitiveMode myDisplayMode;
	int myGridSizeX;
	int myGridSizeY;
	bool isLorenzActive =false;
};
