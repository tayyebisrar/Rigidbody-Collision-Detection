#include <stdio.h>
#include <shapes.h>

void display_vector(Vec2 *v);

int main(void){
    Vec2 test = {2.5, 5.2};
    display_vector(&test);
    return 0;
}

void display_vector(Vec2 *v){
    printf("Vector at Address %p: ", v);
    printf("{%f, %f}\n",v->x, v->y);
}
