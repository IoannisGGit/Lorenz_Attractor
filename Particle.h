#pragma once

#include "ofMain.h"

using namespace glm;

class Particle {
public:
	void setup(vec3 pos, vec3 dir);
	void update(
		float amplitude, float timestep, float restoreForce, float damping,
		int noiseOctaves, float noiseScale, float noiseRate);
	void update(float timestep, float damping, float forceFactor, vec3 target);
	void draw();
	vec3 getPos();
	void setPos(vec3 newpos);//just for debugging purposes
	bool isReady = false;
	
	
private:
	vec3 myPos;
	vec3 myOrigPos;
	vec3 myVel;
	float vecLength = 0;
	float mySize;
};
