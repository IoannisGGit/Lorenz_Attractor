#include "helpers.h"

//--------------------------------------------------------------
float fbm(float x, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofSignedNoise(freq * x);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result;
}

//--------------------------------------------------------------
float fbm(vec2 v2, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofSignedNoise(freq * v2);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result;
}
//--------------------------------------------------------------
float fbm(vec3 v3, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofSignedNoise(freq * v3);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result;
}
//--------------------------------------------------------------
float fbm(vec4 v4, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofSignedNoise(freq * v4);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result;
}

//--------------------------------------------------------------
// Random values used as offsets

const float off0 = 90.44;
const float off1 = 66.38;
const float off2 = 56.27;
const float off3 = 54.31;
const float off4 = 23.22;
const float off5 = 80.44;
const float off6 = 88.73;
const float off7 = 34.16;
const float off8 = 78.05;
const float off9 = 43.40;
const float off10 = 76.67;
const float off11 = 80.67;

//--------------------------------------------------------------
// Noise functions with vec2 results

vec2 fbm_vec2(float x, int numOctaves) {
	return vec2(
		fbm(x, numOctaves),
		fbm(x + off0, numOctaves));
}

vec2 fbm_vec2(vec2 v2, int numOctaves) {
	return vec2(
		fbm(v2, numOctaves), 
		fbm(v2 + vec2(off0, off1), numOctaves));
}

vec2 fbm_vec2(vec3 v3, int numOctaves) {
	return vec2(
		fbm(v3, numOctaves), 
		fbm(v3 + vec3(off0, off1, off2), numOctaves));
}

vec2 fbm_vec2(vec4 v4, int numOctaves) {
	return vec2(
		fbm(v4, numOctaves), 
		fbm(v4 + vec4(off0, off1, off2, off3), numOctaves));
}

//--------------------------------------------------------------
// Noise functions with vec3 results

vec3 fbm_vec3(float x, int numOctaves) {
	return vec3(
		fbm(x, numOctaves),
		fbm(x + off0, numOctaves),
		fbm(x + off1, numOctaves));
}

vec3 fbm_vec3(vec2 v2, int numOctaves) {
	return vec3(
		fbm(v2, numOctaves),
		fbm(v2 + vec2(off0, off1), numOctaves),
		fbm(v2 + vec2(off2, off3), numOctaves));
}

vec3 fbm_vec3(vec3 v3, int numOctaves) {
	return vec3(
		fbm(v3, numOctaves),
		fbm(v3 + vec3(off0, off1, off2), numOctaves),
		fbm(v3 + vec3(off3, off4, off5), numOctaves));
}

vec3 fbm_vec3(vec4 v4, int numOctaves) {
	return vec3(
		fbm(v4, numOctaves),
		fbm(v4 + vec4(off0, off1, off2, off3), numOctaves),
		fbm(v4 + vec4(off4, off5, off6, off7), numOctaves));
}

//--------------------------------------------------------------
// Noise functions with vec3 results

vec4 fbm_vec4(float x, int numOctaves) {
	return vec4(
		fbm(x, numOctaves),
		fbm(x + off0, numOctaves),
		fbm(x + off1, numOctaves),
		fbm(x + off2, numOctaves));
}

vec4 fbm_vec4(vec2 v2, int numOctaves) {
	return vec4(
		fbm(v2, numOctaves),
		fbm(v2 + vec2(off0, off1), numOctaves),
		fbm(v2 + vec2(off2, off3), numOctaves),
		fbm(v2 + vec2(off4, off5), numOctaves));
}

vec4 fbm_vec4(vec3 v3, int numOctaves) {
	return vec4(
		fbm(v3, numOctaves),
		fbm(v3 + vec3(off0, off1, off2), numOctaves),
		fbm(v3 + vec3(off3, off4, off5), numOctaves),
		fbm(v3 + vec3(off6, off7, off8), numOctaves));
}

vec4 fbm_vec4(vec4 v4, int numOctaves) {
	return vec4(
		fbm(v4, numOctaves),
		fbm(v4 + vec4(off0, off1, off2, off3), numOctaves),
		fbm(v4 + vec4(off4, off5, off6, off7), numOctaves),
		fbm(v4 + vec4(off8, off9, off10, off11), numOctaves));
}

//--------------------------------------------------------------
float bias(float x, float b) {
	return x / (((1.0 / b - 2.0)*(1.0 - x)) + 1.0);
}

//--------------------------------------------------------------
float gain(float x, float g) {
	if (x < 0.5)
		return bias(x * 2.0, g) / 2.0;
	else
		return bias(x * 2.0 - 1.0, 1.0 - g) / 2.0 + 0.5;
}

//--------------------------------------------------------------
void calcNormals(ofMesh &curMesh) {
	// Calculates normals for triangle meshes with indices
	// Mesh has to be of type OF_PRIMITIVE_TRIANGLES

	// Quick exit if this isn't a triangle mesh
	if (curMesh.getMode() != OF_PRIMITIVE_TRIANGLES) {
		return;
	}

	// Quick exit if we're not using indices
	if (!curMesh.hasIndices()) {
		return;
	}

	// Since we're using it frequently, store the number of
	// vertices in a local variable
	int numVertices = curMesh.getNumVertices();

	// If we don't already have a normal for each vertex, add them to the mesh
	if (curMesh.getNumNormals() != curMesh.getNumVertices()) {
		curMesh.clearNormals();
		for (int i = 0; i < numVertices; i++) {
			curMesh.addNormal(vec3(0, 0, 0));
		}
	}

	// Get vertex position arrays
	const vector<vec3> vertices = curMesh.getVertices();

	// Initialize an array for an accumulated sum for each normal
	vector<vec3> sumNormals;
	sumNormals.resize(numVertices, vec3(0, 0, 0));

	// Each set of 3 consecutive indices indicates one triangle
	const vector<ofIndexType> indices = curMesh.getIndices();
	int numTriangles = indices.size() / 3;

	// Loop through each triangle
	for (int i = 0; i < numTriangles; i++) {
		// Get indices of the the verts for this triangle
		int v0 = indices[3 * i];
		int v1 = indices[3 * i + 1];
		int v2 = indices[3 * i + 2];

		// Calculate weighted normal due to this triangle
		vec3 d0 = vertices[v1] - vertices[v0];
		vec3 d1 = vertices[v2] - vertices[v0];
		vec3 w = cross(d1, d0);

		// Add weighted value to the normal to the sum at each vertex
		sumNormals[v0] += w;
		sumNormals[v1] += w;
		sumNormals[v2] += w;
	}

	// Loop through each vertex and re-normalize the accumulated sum
	// to calculate the final value for each normal
	for (int i = 0; i < numVertices; i++) {
		curMesh.setNormal(i, normalize(sumNormals[i]));
	}
}
