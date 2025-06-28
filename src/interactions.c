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

    Vector2 AB = subtract_vec2s(&(l->shape.line.point2), &(l->shape.line.point1)); // B - A vector
    Vector2 AC = subtract_vec2s(&(c->shape.circle.center), &(l->shape.line.point1)); // C - A vector

    // Project AC onto AB to find out how far along the line it lies (we just need the scalar, so won't use vector_project())

    float t = dot_product(&AB, &AC) / dot_product(&AB, &AB);

    // if this scalar, t, is less than 0, it means the closest point is A, since the point will be a negative amount of AB away
    // if it's [0, 1], it's perpendicular to AB. If it's more than 1, the closest point is B.

    float dist;

    if (t < 0) {
        dist = vector_distance(&(l->shape.line.point1), &(c->shape.circle.center)); // vector_distance(A, C);
    }
    else if (t >= 0 && t <= 1) {
        Vector2 AConAB = vector_project(&AC, &AB); // The vector produced by projecting AC on AB
        Point P = add_vec2s(&(l->shape.line.point1), &AConAB);
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

int detect_line_line_collision(RigidBody *l1, RigidBody *l2){
    Vector2 A = subtract_vec2s(&(l1->shape.line.point2), &(l1->shape.line.point2)); // direction vector of l1
    Vector2 B = subtract_vec2s(&(l2->shape.line.point2), &(l2->shape.line.point2)); // direction vector of l2

    // Now each line can be defined by l1/l2.point1 + c(A/B) where c is an arbitrary constant
    // l1: p + cA | l2: q + dB

    // PQ = q-p = l2.p1 - l1.p1
    Vector2 PQ = subtract_vec2s(&(l2->shape.line.point1), &(l1->shape.line.point1));

    // cross products of A and B (direction vectors) to determine if line is parallel
    float ABcross = vector_cross2d(&A, &B);
    // cross products of A and PQ (direction and originals' direction) to determine if line is colinear (overlapping)
    float AcrossPQ = vector_cross2d(&A, &PQ);

    if (ABcross == 0) { // parallel
        if (AcrossPQ == 0) { // also colinear with the start points' vector
            return 1; // lines are overlapping, collision
        }
        else{
            return 0; // lines are parallel, separated
        }
    }
    else { // not parallel
        
    }
    

}