#ifndef SHAPES_H
#define SHAPES_H
#include <stdio.h>
#include <parts.h>

typedef struct {
    float radius;
    Vec2 center;
}Circle;

typedef struct {
    Vec2 point1;
    Vec2 point2;
}Line;

typedef struct {
    Vec2* vertices;
    int vertexCount;
}Polygon;

typedef enum {
    CIRCLE,
    LINE,
    POLYGON
}ShapeType;

typedef union {
    Circle circle;
    Line line;
    Polygon polygon;
}ShapeData;

typedef struct{
    ShapeType type;
    Vec2 velocity;
    Vec2 acceleration;
    float rotation;
    float angularVelocity;
    float mass;
    ShapeData shape;
 }RigidBody;

#endif // SHAPES_H