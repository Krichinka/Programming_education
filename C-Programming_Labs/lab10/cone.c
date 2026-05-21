#include "cone.h" 

//стуктура
struct Cone createCone(double radius, double height) {
 struct Cone newCone;
 newCone.r = radius;
 newCone.h = height;
 return newCone;
} 

// объем
double V(struct Cone cone) {
 return (1.0 / 3.0) * P * cone.r * cone.r * cone.h;
} 

// площадь
double S(struct Cone cone) {
 // образующая 
 double l = sqrt(cone.r * cone.r + cone.h * cone.h);
 
 return P * cone.r * (cone.r + l);
} 

//конус
void printCone(struct Cone cone) {
 printf(" Объем: %.2lf\n", V(cone));
 printf(" Площадь поверхности: %.2lf\n\n", S(cone));
}