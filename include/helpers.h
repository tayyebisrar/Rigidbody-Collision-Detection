#ifndef HELPERS_H
#define HELPERS_H
#include <stdio.h>
#include <math.h>
#include "parts.h"

float dot_product(Vec2 *v1, Vec2 *v2);
Vec2 add_vectors(Vec2 *v1, Vec2 *v2);
Vec2 subtract_vectors(Vec2 *v1, Vec2 *v2);
float vector_distance(Vec2 *v1, Vec2 *v2);
Vec2 vector_project(Vec2 *v1, Vec2 *v2);

#endif // HELPERS_H