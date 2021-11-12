#pragma once

#include "ofMain.h"

using namespace glm;

float fbm(float x, int numOctaves = 8);
float fbm(vec2 v2, int numOctaves = 8);
float fbm(vec3 v3, int numOctaves = 8);
float fbm(vec4 v4, int numOctaves = 8);

vec2 fbm_vec2(float x, int numOctaves = 8);
vec2 fbm_vec2(vec2 v2, int numOctaves = 8);
vec2 fbm_vec2(vec3 v3, int numOctaves = 8);
vec2 fbm_vec2(vec4 v4, int numOctaves = 8);

vec3 fbm_vec3(float x, int numOctaves = 8);
vec3 fbm_vec3(vec2 v2, int numOctaves = 8);
vec3 fbm_vec3(vec3 v3, int numOctaves = 8);
vec3 fbm_vec3(vec4 v4, int numOctaves = 8);

vec4 fbm_vec4(float x, int numOctaves = 8);
vec4 fbm_vec4(vec2 v2, int numOctaves = 8);
vec4 fbm_vec4(vec3 v3, int numOctaves = 8);
vec4 fbm_vec4(vec4 v4, int numOctaves = 8);

float bias(float x, float b);
float gain(float x, float g);

void calcNormals(ofMesh &curMesh);
