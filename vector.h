#ifndef vector_H
#define vector_H
#include <iostream>
#include <math.h>

class vector{
	private:
		float x;
		float y;
		float z;
	
	public:
		//initialize the vector (or maybe point)
		void set_xyz(float input1, float input2, float input3);
		
		//dot-product v1.dot(v2) -> v1 . v2
		float dot(vector other);
		
		//addition v1.plus(v2) -> v1 + v2
		vector plus(vector other);
		
		//subtraction v1.minus(v2) -> v1 - v2 
		vector minus(vector other);
		
		//multiply by magnitude 
		vector magmult(float a);
		
		//divide by magnitude 
		vector overmag(float a);
		
		float get_mag();
		
		vector make_unit();
		
		void print();
};



//......set_xyz//==========================================================
void vector::set_xyz(float input1, float input2, float input3){
	x = input1;
	y = input2;
	z = input3;
	return;
}
//=========================================================================


//......dot//==============================================================
float vector::dot(vector other){
	return (this->x*other.x)+(this->y*other.y)+(this->z*other.z);
}
//=========================================================================


//......plus//=============================================================
vector vector::plus(vector other){
	vector newv;
	float xn = this->x+other.x;
	float yn = this->y+other.y;
	float zn = this->z+other.z;
	newv.set_xyz(xn, yn, zn);
	
	return newv;
}
//=========================================================================


//......minus//============================================================
vector vector::minus(vector other){
	vector newv;
	float xn = this->x-other.x;
	float yn = this->y-other.y;
	float zn = this->z-other.z;
	newv.set_xyz(xn, yn, zn);
	
	return newv;
}
//=========================================================================


//......magmult//==========================================================
vector vector::magmult(float a){
	x = x*a;
	y = y*a;
	z = z*a;
	vector newv;
	newv.set_xyz(x,y,z);
	return newv;
}
//=========================================================================


//......overmag//==========================================================
vector vector::overmag(float a){
	x = x/a;
	y = y/a;
	z = z/a;
	vector newv;
	newv.set_xyz(x,y,z);
	return newv;
}
//=========================================================================


//......get_mag//==========================================================
float vector::get_mag(){
	float mx = pow(x, 2);
	float my = pow(y, 2);
	float mz = pow(z, 2);
	
	return pow((mx+my+mz),0.5);
}
//=========================================================================


//......make_unit//========================================================
vector vector::make_unit(){
	vector t;
	t.set_xyz(x,y,z);
	return t.overmag(t.get_mag());
	
}
//=========================================================================


//......print//============================================================
void vector::print(){
	std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
	return;
}
//=========================================================================

#endif