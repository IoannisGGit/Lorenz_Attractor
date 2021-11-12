#include "ParticleSystem.h"
#include "helpers.h"

//--------------------------------------------------------------
void ParticleSystem::setupPlane(int gridSizeX, int gridSizeY, float planeRangeX, float planeRangeY, ofPrimitiveMode displayMode) {
	// Clear any existing particle and mesh data
	myParticles.clear();
	myMesh.clear();

	// Store grid size values into member variables
	myGridSizeX = gridSizeX;
	myGridSizeY = gridSizeY;

	// Set the display mode
	myDisplayMode = displayMode;
	myMesh.setMode(myDisplayMode);

	// Initialize the particles
	for (int i = 0; i < myGridSizeX; i++)
		for (int j = 0; j < myGridSizeY; j++) {
			vec3 pos = vec3(
				ofMap(i, 0, myGridSizeX - 1, -0.5 * planeRangeX, 0.5 * planeRangeX),
				0.0,
				ofMap(j, 0, myGridSizeY - 1, -0.5 * planeRangeY, 0.5 * planeRangeY));
			vec3 dir = vec3(0, 1, 0);
			Particle par;
			par.setup(pos, dir);
			myParticles.push_back(par);
		}

	// Create a vertex for each particle
	for (int i = 0; i < myParticles.size(); i++) {
		vec3 pos = myParticles[i].getPos();
		myMesh.addVertex(pos);
	}

	// Initialize the mesh
	if (myDisplayMode == OF_PRIMITIVE_POINTS) {
		// For points we don't need to declare anything more
	}
	else if (myDisplayMode == OF_PRIMITIVE_LINES) {
		// Declare lines connecting the vertices in a square grid using the vertex indices
		// We add lines by creating a list of pairs of vertex indices that should be
		// connected by lines
		for (int i = 0; i < myGridSizeX; i++) {
			for (int j = 0; j < myGridSizeY; j++) {
				if (i < myGridSizeX - 1) {
					myMesh.addIndex(getParticleIndex(i, j));
					myMesh.addIndex(getParticleIndex(i + 1, j));
				}

				if (j < myGridSizeY - 1) {
					myMesh.addIndex(getParticleIndex(i, j));
					myMesh.addIndex(getParticleIndex(i, j + 1));
				}
			}
		}
	}
	else if (myDisplayMode == OF_PRIMITIVE_TRIANGLES) {
		// Declare two triangles for each square in the grid
		for (int i = 0; i < myGridSizeX - 1; i++) {
			for (int j = 0; j < myGridSizeY - 1; j++) {
				myMesh.addTriangle(
					getParticleIndex(i, j),
					getParticleIndex(i + 1, j),
					getParticleIndex(i + 1, j + 1));

				myMesh.addTriangle(
					getParticleIndex(i, j),
					getParticleIndex(i + 1, j + 1),
					getParticleIndex(i, j + 1));
			}
		}

		// Add a normal for each vertex. This can be done by calling the
		// calcNormals helper function
		calcNormals(myMesh);
	}
	else {
		ofLogError("ParticleSystem::setup, displayMode set to invalid value");
	}
	
}

//--------------------------------------------------------------
void ParticleSystem::setupSphere(int gridSizeX, int gridSizeY, float sphereRadius, ofPrimitiveMode displayMode) {
	// Setting up particles into a initial spherical formation

	// Clear any existing particle and mesh data
	myParticles.clear();
	myMesh.clear();
	myParticles2.clear();

	// Store grid size values into member variables
	myGridSizeX = gridSizeX;
	myGridSizeY = gridSizeY;

	// Set the display mode
	myDisplayMode = displayMode;
	myMesh.setMode(myDisplayMode);
	myMesh.enableNormals();
	glPointSize(2);

	// Initialize the particles
	vec3 pos;
	for (int i = 0; i < myGridSizeX; i++)
		for (int j = 0; j < myGridSizeY; j++) {
			// Use spherical co-ordinates to calculate initial position
			float theta = ofDegToRad(ofMap(i, 0, myGridSizeX, 360.0, 0.0));
			float phi = ofDegToRad(ofMap(j, -1, myGridSizeY, 0.0, 180.0));
			vec3 pos = sphereRadius * vec3(sin(phi) * cos(theta), cos(phi), sin(phi) * sin(theta));
			vec3 dir = normalize(pos);
			Particle par;
			par.setup(pos, dir);
			myParticles.push_back(par);
		}

	// Create additional particles for the top and bottom
	Particle topParticle;
	topParticle.setup(vec3(0, sphereRadius, 0), vec3(0, 1, 0));
	int topParticleIndex = myParticles.size();
	myParticles.push_back(topParticle);

	Particle bottomParticle;
	bottomParticle.setup(vec3(0, -sphereRadius, 0), vec3(0, -1, 0));
	int bottomParticleIndex = myParticles.size();
	myParticles.push_back(bottomParticle);

	// Create a vertex for each particle
	for (int i = 0; i < myParticles.size(); i++) {
		vec3 pos = myParticles[i].getPos();
		myMesh.addVertex(pos);
		//myMesh.addColor(ofFloatColor(0.2, 0.5, 0.7));
		myMesh.addColor(ofFloatColor(0.0, 0.0, 1.0));

	}

	// Initialize the mesh
	if (myDisplayMode == OF_PRIMITIVE_POINTS) {
		// For points we don't need to declare anything more
	}
	else if (myDisplayMode == OF_PRIMITIVE_LINES) {
		// Declare lines connecting the vertices in a square grid using the vertex indices
		// We add lines by creating a list of pairs of vertex indices that should be
		// connected by lines
		for (int i = 0; i < myGridSizeX; i++) {
			for (int j = 0; j < myGridSizeY; j++) {

				myMesh.addIndex(getParticleIndex(i, j));
				myMesh.addIndex(getParticleIndex(i + 1, j));

				if (j < myGridSizeY - 1) {
					myMesh.addIndex(getParticleIndex(i, j));
					myMesh.addIndex(getParticleIndex(i, j + 1));
				}
			}
		}

		// Connect the bottom and top verices to all the other vertices in the first and last rows
		for (int i = 0; i < myGridSizeX; i++) {
			myMesh.addIndex(topParticleIndex);
			myMesh.addIndex(getParticleIndex(i, 0));

			myMesh.addIndex(bottomParticleIndex);
			myMesh.addIndex(getParticleIndex(i, myGridSizeY - 1));
		}
	}
	else if (myDisplayMode == OF_PRIMITIVE_TRIANGLES) {
		// Declare two triangles for each square in the grid
		for (int i = 0; i < myGridSizeX; i++) {
			for (int j = 0; j < myGridSizeY - 1; j++) {
				myMesh.addTriangle(
					getParticleIndex(i, j),
					getParticleIndex(i + 1, j),
					getParticleIndex(i + 1, j + 1));

				myMesh.addTriangle(
					getParticleIndex(i, j),
					getParticleIndex(i + 1, j + 1),
					getParticleIndex(i, j + 1));
			}
		}

		// Connect the bottom and top verices to all the other vertices in the first and last rows
		for (int i = 0; i < myGridSizeX; i++) {
			myMesh.addTriangle(
				topParticleIndex,
				getParticleIndex(i + 1, 0),
				getParticleIndex(i, 0));

			myMesh.addTriangle(
				bottomParticleIndex,
				getParticleIndex(i, myGridSizeY - 1),
				getParticleIndex(i + 1, myGridSizeY - 1));
		}

		// Add a normal for each vertex. This can be done by calling the
		// calcNormals helper function
		calcNormals(myMesh);
	}
	else {
		ofLogError("ParticleSystem::setup, displayMode set to invalid value");
	}
	
	
}

//--------------------------------------------------------------
void ParticleSystem::update(float amplitude, float timestep, float restoreForce, float damping,int noiseOctaves,float noiseScale, float noiseRate) {
	for (int i = 0; i < myParticles.size(); i++) {
		myParticles[i].update(amplitude, timestep,restoreForce,damping,noiseOctaves,noiseScale,noiseRate);
		myMesh.setVertex(i, myParticles[i].getPos());
		
	}
	if(isLorenzActive){
		transferParticles(transferTime, transferNum);
	
		for (int i = 0; i < myParticles2.size(); i++) {
			if (!myParticles2[i].isReady) {
				myParticles2[i].update(timestep, damping, 5, center);
			}else {
				myParticles2[i].setPos(lorenzAttractor(myParticles2[i].getPos()));
			}
			if (i % 2 ==0) {
				myMesh.setVertex(i + myParticles.size(), -myParticles2[i].getPos() - offset);
				myMesh.setColor(i + myParticles.size(), ofFloatColor(1.0, 0.0, 0.0));
			}
			else { 
				myMesh.setVertex(i + myParticles.size(), myParticles2[i].getPos() - offset);
				myMesh.setColor(i + myParticles.size(), ofFloatColor(0.0, 1.0, 0.0));
			}
		}
		counter++;
	}
	
	// If we've got a mesh of triangles we need to update the vertex normals
	if (myDisplayMode == OF_PRIMITIVE_TRIANGLES) {
		calcNormals(myMesh);
	}
	
	
}

//--------------------------------------------------------------
void ParticleSystem::draw() {
	myMesh.draw();
}

//--------------------------------------------------------------
int ParticleSystem::getParticleIndex(int x, int y) {
	x = ofWrap(x, 0, myGridSizeX);
	y = ofWrap(y, 0, myGridSizeY);
	return myGridSizeY * x + y;
}

void ParticleSystem::transferParticles(int time, int numParticles) {
	
	if (counter % time == 0 && myParticles.size() > 0 ) {

		if (numParticles > myParticles.size()) numParticles = 1;

		for(int i=0; i<numParticles;i++){
			transferIndex = int(ofRandom(0, myParticles.size()));
			swapParticles(transferIndex);
		}
		
	}

}
void ParticleSystem::swapParticles(int index) {
	//transfer particles from one array to the other
	myParticles2.push_back(myParticles[index]);
	myParticles.erase(myParticles.begin() + index);
}

vec3 ParticleSystem::lorenzAttractor(vec3 pos) {

	/*Lorenz equations
	dx/dt = sigma(y-x)
	dy/dy = x(ro-z)-y
	dz/dt = xy -beta z
	*/
	ofTranslate(1000, 0, 0);
	float x = pos.x;
	float y = pos.y;
	float z = pos.z;

	float timestep = 0.01;
	float sigma = 10;
	float beta = 8.0 / 3.0;
	float ro = 28;
	float roMin = ofMap(cos(ofGetElapsedTimef()*0.05), 1, -1, 28, 0);
	float mappedRo = ofMap(cos(ofGetElapsedTimef()), 1, -1, roMin, 28);

	float dx = (sigma * (y - x))* timestep;
	float dy = (x * (mappedRo - z) - y)* timestep;
	float dz = (x * y - beta * z)* timestep;
	
	x += dx;
	y += dy;
	z += dz;
	return vec3(x, y, z);
}

void ParticleSystem::activateLorenz(bool active) {
	if (active) {
		isLorenzActive = true;
		transferIndex = 0;
		counter = 0;
	}else isLorenzActive = false;
}


void ParticleSystem::setTransferNum(int num) {
	transferNum = num;
	
}