#ifndef SHAPES_H
#define SHAPES_H
#include <stdio.h>
#include <parts.h>

typedef struct {
    float radius;
    Point center;
}Circle;

typedef struct {
    Point point1;
    Point point2;
}Line;

typedef struct {
    Point* vertices;
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
    Vector2 velocity;
    Vector2 acceleration;
    float rotation;
    float angularVelocity;
    float mass;
    ShapeData shape;
 }RigidBody;

#endif