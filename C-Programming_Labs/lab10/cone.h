#ifndef CONE_H
#define CONE_H
#include <stdio.h>
#include <math.h> 

#define P 3.141592 

struct Cone {
 double r;
 double h; 
}; 
struct Cone createCone(double radius, double height);
double V(struct Cone cone);
double S(struct Cone cone);
void printCone(struct Cone cone);
#endif