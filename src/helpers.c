#include <stdio.h>
#include <math.h>
#include "parts.h"

float dot_product(Vec2 *v1, Vec2 *v2){
    // v1 ⋅ v2
    return ((v1->x * v2->x) + (v1->y * v2->y));
}
Vec2 add_vectors(Vec2 *v1, Vec2 *v2){
    // v1 + v2
    return (Vec2){v1->x + v2->x, v1->y + v2->y};
}

Vec2 subtract_vectors(Vec2 *v1, Vec2 *v2){
    // v1 - v2
    return (Vec2){v1->x - v2->x, v1->y - v2->y};
}
float vector_distance(Vec2 *v1, Vec2 *v2){
    // distance between v1 and v2
    return sqrt(((v1->x - v2->x) * (v1->x - v2->x))+((v1->y - v2->y) * (v1->y - v2->y)));
}

float vector_magnitude(Vec2 *v){
    // size of v, pythagoras
    return sqrt((v->x * v->x) + (v->y * v->y));
}

Vec2 vector_project(Vec2 *v1, Vec2 *v2){
    // Project v1 onto v2, i.e. the shadow v1 casts on v2, or how far along v2 that v1 lies.
    float mt = dot_product(v1, v2) / dot_product(v2, v2);
    return (Vec2){v2->x * mt, v2->y * mt};
}