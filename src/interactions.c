#include <stdio.h>
#include <math.h>
#include <shapes.h>
#include <helpers.h>

int detect_circles_collision(RigidBody *c1, RigidBody* c2){
    // If distance between centres is less than sum of radii
    if (vector_distance(&(c1->shape.circle.center), &(c2->shape.circle.center)) <= c1->shape.circle.radius + c2->shape.circle.radius) {
        return 1;
    }
    return 0;
}

int detect_circle_line_collision(RigidBody *c, RigidBody *l){
    // shortest distance from circle centre to line should be less than or equal to circle radius

    Vec2 AB = subtract_vectors(&(l->shape.line.point2), &(l->shape.line.point1)); // B - A vector
    Vec2 AC = subtract_vectors(&(c->shape.circle.center), &(l->shape.line.point1)); // C - A vector

    // Project AC onto AB to find out how far along the line it lies (we just need the scalar, so won't use vector_project())

    float t = dot_product(&AB, &AC) / dot_product(&AB, &AB);

    // if this scalar, t, is less than 0, it means the closest point is A, since the point will be a negative amount of AB away
    // if it's [0, 1], it's perpendicular to AB. If it's more than 1, the closest point is B.

    float dist;

    if (t < 0) {
        dist = vector_distance(&(l->shape.line.point1), &(c->shape.circle.center)); // vector_distance(A, C);
    }
    else if (t >= 0 && t <= 1) {
        Vec2 AConAB = vector_project(&AC, &AB); // The vector produced by projecting AC on AB
        Vec2 P = add_vectors(&(l->shape.line.point1), &AConAB);
        dist = vector_distance(&(P), &(c->shape.circle.center));
    }
    else {
        dist = vector_distance(&(l->shape.line.point2), &(c->shape.circle.center)); // vector_distance(B, C);
    }

    if (dist <= c->shape.circle.radius){
        return 1; // collision
    }
    else{
        return 0; // no collision
    }

}