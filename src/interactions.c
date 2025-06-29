#include <stdio.h>
#include <math.h>
#include <shapes.h>
#include <helpers.h>

#define EPSILON 1e-9f

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
    Vector2 AB = subtract_vec2s(&(l1->shape.line.point2), &(l1->shape.line.point1)); // direction vector of l1
    Vector2 CD = subtract_vec2s(&(l2->shape.line.point2), &(l2->shape.line.point1)); // direction vector of l2

    // Now each line can be defined by l1/l2.point1 + c(AB/CD) where c is an arbitrary constant between 0 and 1
    // l1: p + λAB | l2: q + μCD

    // PQ = q-p = l2.p1 - l1.p1
    Vector2 PQ = subtract_vec2s(&(l2->shape.line.point1), &(l1->shape.line.point1));

    // cross products of A and B (direction vectors) to determine if line is parallel
    float ABcrossCD = vector_cross2d(&AB, &CD);
    // cross products of A and PQ (direction and originals' direction) to determine if line is colinear (overlapping)
    float ABcrossPQ = vector_cross2d(&AB, &PQ);
    
    
    if (fabsf(ABcrossCD) < EPSILON) { // parallel - use epsilon for float inaccuracies
        if (ABcrossPQ < EPSILON) { // also colinear with the start points' vector   
            // project the colinear segments onto a single line (their direction, AB/CD/PQ)

            Vector2 colinear_dir = unit_vec2(&AB); // unit vector for direction, means projection loses denominator and just leaves unit dot vector
            // make sure all points lay along the line to accurately find endpoints w/ no distortion, so go from a0 (l1.p1) onwards
            // or, to save computation, just go from the points themselves, since each vector is defined globally from the origin, and are all
            // in the same direction - creates 4 values representing where the points are
            float a0 = dot_product(&l1->shape.line.point1, &colinear_dir); 
            float a1 = dot_product(&l1->shape.line.point2, &colinear_dir);
            float b0 = dot_product(&l2->shape.line.point1, &colinear_dir);
            float b1 = dot_product(&l2->shape.line.point2, &colinear_dir);

            // determine if there is overlap
            float amin = fminf(a0, a1), amax = fmaxf(a0, a1);
            float bmin = fminf(b0, b1), bmax = fmaxf(b0, b1);

            if (amax >= bmin && bmax >= amin){
                return 1; // collision
            }
            else{ // readability else
                return 0; // no collision - lines are colinear but separated
            }
        }
        else{
            return 0; // lines are parallel but separated  
        }
    }
    else { // not parallel - evaluate for 
        float lambda = vector_cross2d(&PQ, &CD)/vector_cross2d(&AB, &CD);
        float mu = vector_cross2d(&PQ, &AB)/vector_cross2d(&AB, &CD);

        if (lambda >= 0 && lambda <= 1 && mu >= 0 && mu <= 1){
            return 1; // intersection lies between the lines, collision!
            // collision point would be the intersection, or p + λAB/q + μCD
        }
        else{
            return 0; // intersection doesn't exist
        }
    }
}