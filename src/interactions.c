#include <stdio.h>
#include <math.h>
#include <shapes.h>

int detect_circles_collision(RigidBody *c1, RigidBody* c2){
    float xDistance = (c1->position.x - c2->position.x);
    float yDistance = (c1->position.y - c2->position.y);

    if (sqrt((xDistance * xDistance) + (yDistance * yDistance)) <= c1->shape.circle.radius + c2->shape.circle.radius) {
        return 1;
    }

    return 0;
}

int detect_circle_line_collision(RigidBody *c, RigidBody *l){
    Vec2 AB = Vec2 
}