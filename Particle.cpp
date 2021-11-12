#include "Particle.h"
#include "helpers.h"

//--------------------------------------------------------------
void Particle::setup(vec3 pos, vec3 dir) {
	myPos = pos;
	myOrigPos = pos;
	myVel = vec3(0.0, 0.0, 0.0);
	mySize = 0.1;
}

//--------------------------------------------------------------
void Particle::update(float amplitude, float timestep, float restoreForce, float damping, int noiseOctaves, float noiseScale, float noiseRate) {
	
	myVel += amplitude * timestep * fbm_vec3(vec4(
			myPos.x/noiseScale,
			myPos.y/noiseScale,
			myPos.z/noiseScale,
			noiseRate*ofGetElapsedTimef()),
			noiseOctaves);
	myVel += timestep * restoreForce*(myOrigPos - myPos);
	myVel -= timestep * damping * myVel;
	myPos += myVel * timestep;
}

void Particle::update(float timestep, float damping, float forceFactor, vec3 target) {
	vec3 forceVector = (target - myPos);
	vecLength = length(forceVector);
	vec3 force = normalize(forceVector) * forceFactor*timestep;
	myVel += timestep * force;
	myVel -= timestep * damping * myVel;
	if (vecLength > 1) {
		myPos += myVel * timestep;
		
	}
	else {
		isReady = true;
	}
	
}

//--------------------------------------------------------------
void Particle::draw() {
	ofDrawSphere(myPos, mySize);
}

//--------------------------------------------------------------
vec3 Particle::getPos() {
	return myPos;
}

void Particle::setPos(vec3 newpos) {
	myPos = newpos;
}
