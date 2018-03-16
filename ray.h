#ifndef ray_H
#define ray_h
#include "vector.h"
#include <iostream>

class ray{
	public:
	vector point;
	vector direction;
	
	ray(vector pt, vector dir);
	
};

//......constructor//======================================================
ray::ray(vector pt, vector dir){
	point = pt;
	direction = dir;
}
//=========================================================================


#endif