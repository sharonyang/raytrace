#ifndef MAIN_HPP
#define MAIN_HPP

#include <algorithm>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "RT_Vec3.hpp"
#include "RT_Object.hpp"
#include "RT_Floor.hpp"
#include "RT_Sphere.hpp"
#include "RT_Shape.hpp"
#include "InputParse.hpp"
#include "LightSource.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"

#define IMAGE_HEIGHT 512
#define IMAGE_WIDTH 512
#define VIEW_HEIGHT 80
#define VIEW_WIDTH 80
#define MAX_DISTANCE 1000000
#define TRACE_DEPTH 3
#define EPSILON 0.0001
#define SCREEN_Z 30

using namespace std;

vector<RT_Object*> object_list;
vector<LightSource*> light_list;
RT_Vec3 cam_position(0.0f, 0.0f, 90.0f);
RT_Vec3 globalLight(1.0f, 1.0f, 1.0f);

double HALF_PIXEL_WIDTH = double(VIEW_WIDTH) / double(IMAGE_WIDTH * 2.0f);
double HALF_PIXEL_HEIGHT = double(VIEW_HEIGHT) / double(IMAGE_HEIGHT * 2.0f);
double PIXEL_WIDTH = double(VIEW_WIDTH) / double(IMAGE_WIDTH);
double PIXEL_HEIGHT = double(VIEW_HEIGHT) / double(IMAGE_HEIGHT);
int progress = 0;
int real_try = -1;
bool multiple_object = false;
bool multiple_light = false;

/* Prototypes */
RT_Vec3 put_pixel(int i, int j);
void shape_retrieve(RT_Shape* curr_shape, const char* file_path, \
	int size, int vert_size, int face_size, RT_Vec3 loc);
void draw_objects();
void light_source();
void init();
void print_progress(int curr_step);
void reshape(int width, int height);
void display();
void parse_argument(int argc, char **argv);

#endif
