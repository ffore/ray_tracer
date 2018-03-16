#include "CImg.h"
#include "vector.h"
#include "sphere.h"
#include "ray.h"
#include <iostream>
#include <math.h>
using namespace cimg_library;

//======is_hit=============================================================
bool is_hit(ray r, sphere s, vector w);
//=========================================================================


//======get_spt============================================================
vector get_spt(ray r, sphere s, vector w);
//=========================================================================


//======get_diffuse========================================================
float get_diffuse(vector n, vector l, float kd, float I);
//=========================================================================


//======get_specular=======================================================
float get_specular(vector v, vector n, vector l, float ks, float I, float p);
//=========================================================================


//======get_ambient========================================================
float get_ambient(float ka, float I);
//=========================================================================


int main(){
	//CImg stuff
	CImg<unsigned char> img(256,256,1,3);		// 256x256 the value 1 is for dz (depth) and 3 is for RGB	
	
	vector camera;
	camera.set_xyz(0,0,0);
	
	sphere s1(0.7,0.35,0.5, 0.22, 100,50,30);
	sphere s2(0.3,0.7,0.5, 0.17, 10,190,3);
	
	//coordinate system
	vector lookAt;
	lookAt.set_xyz(0,0,-1);	//experiment1 in part2 of report
	//lookAt.set_xyz(0.25,-0.25,-1);	//experiment 2 in part2 of report
	vector outU;
	outU.set_xyz(1,0,0);
	vector upV;
	upV.set_xyz(0,1,0);
	vector lightDir;
	
	/*different light direction vectors to use */
	//lightDir.set_xyz(0, 3, 0);	//works w/ (diffuse) not specular
	
	lightDir.set_xyz(0,-1,1);	//works w/ specular (I = 0.5, p = 5)alone & diffuse alone & (diffuse + specular) & & (diffuse + specular + ambient)
	
	//lightDir.set_xyz(-1,-0.4,1); //i was playing with this one for specular
	
	//lightDir.set_xyz(1/(pow(2, 0.5)), 0, 1/(pow(2, 0.5))); //this is a unit vector doesn't work on specular
	
	//lightDir.set_xyz(1, 3, 1.1); //last one distorts color z is too far from 1
	
	
	for(float i = 0; i < 256; i++){
		for(float j = 0; j < 256; j++){
			float u = (i+0.5)/256;
			float v = (j+0.5)/256;			
			//vector p = ((outU.magmult(u)).plus(upV.magmult(v))).plus(camera);
			vector p;
			p.set_xyz(u,v,0);
			
			//p.print();
			ray traceRay(p, lookAt);
			if(is_hit(traceRay, s1, lookAt)){
				// /*intersection (no shading)*/
				// img(i,j,0,0) = s1.get_r();
				// img(i,j,0,1) = s1.get_g();
				// img(i,j,0,2) = s1.get_b();
				
				// /*diffuse only*/
				// img(i,j,0,0) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_r(), 0.5);
				// img(i,j,0,1) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_g(), 0.5);
				// img(i,j,0,2) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_b(), 0.5);
				
				// /*specular only*/
				// img(i,j,0,0) = get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, 220, 0.5, 10);
				// img(i,j,0,1) = get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, 220, 0.5, 10);
				// img(i,j,0,2) = get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, 220, 0.5, 10);
				
				// /*ambient only*/
				// img(i,j,0,0) = get_ambient(s1.get_r(), .5);
				// img(i,j,0,1) = get_ambient(s1.get_g(), .5);
				// img(i,j,0,2) = get_ambient(s1.get_b(), .5);
				
				// /*diffuse + specular*/
				// img(i,j,0,0) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_r(), 0.5) + get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, (220-s1.get_r()), 0.5, 10);
				// img(i,j,0,1) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_g(), 0.5) + get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, (220-s1.get_g()), 0.5, 10);
				// img(i,j,0,2) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_b(), 0.5) + get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, (220-s1.get_b()), 0.5, 10);
			
				/*diffuse + specular + ambient*/
				img(i,j,0,0) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_r(), 0.5) + get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, (220-s1.get_r()), 0.5, 10) + get_ambient(s1.get_r(), .2);
				img(i,j,0,1) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_g(), 0.5) + get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, (220-s1.get_g()), 0.5, 10) + get_ambient(s1.get_g(), .2);
				img(i,j,0,2) = get_diffuse(s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, s1.get_b(), 0.5) + get_specular(lookAt, s1.get_normal(get_spt(traceRay, s1, lookAt)), lightDir, (220-s1.get_b()), 0.5, 10) + get_ambient(s1.get_b(), .2);
			
			}
			 if(is_hit(traceRay, s2, lookAt)){
				// /*intersection (no shading)*/
				// img(i,j,0,0) = s2.get_r();
				// img(i,j,0,1) = s2.get_g();
				// img(i,j,0,2) = s2.get_b();
				
				// /*diffuse only*/
				// img(i,j,0,0) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_r(), 0.2);
				// img(i,j,0,1) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_g(), 0.2);
				// img(i,j,0,2) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_b(), 0.2);
				
				// /*specular only*/
				// img(i,j,0,0) = get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, 220, 0.5, 25);
				// img(i,j,0,1) = get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, 220, 0.5, 25);
				// img(i,j,0,2) = get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, 220, 0.5, 25);
				
				// /*ambient only*/
				// img(i,j,0,0) = get_ambient(s2.get_r(), .5);
				// img(i,j,0,1) = get_ambient(s2.get_g(), .5);
				// img(i,j,0,2) = get_ambient(s2.get_b(), .5);
				
				// /*diffuse + specular*/
				// img(i,j,0,0) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_r(), 0.2) + get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, (220-s2.get_r()), 0.5, 5);
				// img(i,j,0,1) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_g(), 0.2) + get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, (220-s2.get_g()), 0.5, 5);
				// img(i,j,0,2) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_b(), 0.2) + get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, (220-s2.get_b()), 0.5, 5);
				
				/*diffuse + specular + ambient*/
				img(i,j,0,0) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_r(), 0.2) + get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, (220-s2.get_r()), 0.5, 5) + get_ambient(s2.get_r(), .2);
				img(i,j,0,1) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_g(), 0.2) + get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, (220-s2.get_g()), 0.5, 5) + get_ambient(s2.get_g(), .2);
				img(i,j,0,2) = get_diffuse(s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, s2.get_b(), 0.2) + get_specular(lookAt, s2.get_normal(get_spt(traceRay, s2, lookAt)), lightDir, (220-s2.get_b()), 0.5, 5) + get_ambient(s2.get_b(), .2);

				
			 }
			
		}
	}
	
	img.display("my window");
	
	return 0;
}

//======is_hit=============================================================
bool is_hit(ray r, sphere s, vector w){
	//get discriminant 
	float d = (w.dot(r.point.minus(s.center)))*(w.dot(r.point.minus(s.center)))-((w.dot(w))*((r.point.minus(s.center)).dot(r.point.minus(s.center))-(s.radius*s.radius)));
	if(d >= 0){
		return true;
	}
	return false;
}
//=========================================================================


//======get_spt============================================================
vector get_spt(ray r, sphere s, vector w){
	//float disc = (w.dot(r.point.minus(s.center)))*(w.dot(r.point.minus(s.center)))-((w.dot(w))*((r.point.minus(s.center)).dot(r.point.minus(s.center))-(s.radius*s.radius)));
	
	//this will only be used when the disc is positive or zero
	
	//A
	float A = w.dot(w);
	
	//B
	float B = (w.magmult(2)).dot(r.point.minus(s.center));
	
	//C
	float C = ((r.point.minus(s.center)).dot(r.point.minus(s.center)))-(pow(s.radius, 2));
	
	float disc = (pow(B, 2) - (4*A*C));
	
	float t;
	if(disc == 0){
		//t = -1*(w.dot((r.point).minus(s.center)))/(w.dot(w));
		t = (-1*B)/(2*A);
	}
	else{
		//float t1 = -1*((w.dot((r.point).minus(s.center))) + pow(disc, 0.5))/(w.dot(w));
		//float t2 = -1*((w.dot((r.point).minus(s.center))) - pow(disc, 0.5))/(w.dot(w));
		
		float t1 = ((-1*B) + pow((pow(B,2)-4*A*C), 0.5))/(2*A);
		float t2 = ((-1*B) - pow((pow(B,2)-4*A*C), 0.5))/(2*A);
		if(t1 < t2)
			t = t1;
		else
			t = t2;
	}
	vector v_tr = (r.point).plus(w.magmult(t));
	//v_tr.print();
	return v_tr;
}
//=========================================================================


//======get_diffuse========================================================
float get_diffuse(vector n, vector l, float kd, float I){
	float max = n.dot(l);
	if(max < 0){
		return 0;
	}
	else{
		float val_tr = kd*I*max;
		return val_tr;
	}
}
//=========================================================================


//======get_specular=======================================================
float get_specular(vector v, vector n, vector l, float ks, float I, float p){
	//need to calculate h = (v+l)/(||v+l||)
	vector num = v.plus(l);
	vector h = num.overmag(num.get_mag());
	
	float max = n.dot(h);
	if(max < 0){
		return 0;
	}
	else{
		float val_tr = ks*I*pow(max,p);
		return val_tr;
	}
}
//=========================================================================


//======get_ambient========================================================
float get_ambient(float ka, float I){
	return ka*I;
}
//=========================================================================

