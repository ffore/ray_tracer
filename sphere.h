#ifndef sphere_H
#define sphere_H
#include "vector.h"
#include <iostream>

class sphere{	
	public:
		float radius;
		vector center;
		sphere(float nx, float ny, float nz, float nr, float red, float green, float blue);
		float r;
		float g;
		float b;
		void print();
		float get_r();
		float get_g();
		float get_b();
		vector get_normal(vector p);
};

//......constructor//======================================================
sphere::sphere(float nx, float ny, float nz, float nr, float red, float green, float blue){
	center.set_xyz(nx, ny, nz);
	radius = nr;
	r = red;
	g = green;
	b = blue;
}
//=========================================================================


//......print//============================================================
void sphere::print(){
	center.print();
	std::cout << "radius: " << radius << std::endl;
	return;
}
//=========================================================================


//......get_r//============================================================
float sphere::get_r(){
	return r;
}
//=========================================================================


//......get_g//============================================================
float sphere::get_g(){
	return g;
}
//=========================================================================


//......get_b//============================================================
float sphere::get_b(){
	return b;
}
//=========================================================================


//......get_normal//=======================================================
vector sphere::get_normal(vector p){
	//vector n = (p.minus(center)).magmult(2); 
	vector n = (p.minus(center)).overmag(radius);
	//n.print();
	return n;
}
//=========================================================================
#endif