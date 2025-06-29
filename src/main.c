#include <stdio.h>
#include "shapes.h"
#include "helpers.h"

void display_vector(Vec2 *v);

int main(void){
    Vector2 test = {3, 4};
    display_vector(&test);
    Vector2 unit_test = unit_vec2(&test);
    display_vector(&unit_test);
    return 0;
}

void display_vector(Vec2 *v){
    printf("Vector at Address %p: ", v);
    printf("{%f, %f}\n",v->x, v->y);
}
