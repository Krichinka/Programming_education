#include "cone.h" 

int main() {
 int N;
 printf("Введите количество конусов: ");
 scanf("%d", &N);
 
 
 struct Cone cones[N];
    cones[1].r = 2;
    printf("%lf", cones[1].r);
 
 
 for (int i = 0; i < N; i++) {
 double radius, height;
 printf("\nКонУс %d:\n", i + 1);
 printf("Введите радиус основания: ");
 scanf("%lf", &radius);
 printf("Введите высоту: ");
 scanf("%lf", &height);
 
 
 cones[i] = createCone(radius, height);
 }
 
 printf("Результат\n");
 
 
 for (int i = 0; i < N; i++) {
 printf("Конус %d:\n", i + 1);
 // Используем функцию 
 printCone(cones[i]);
 }
 return 0;
}