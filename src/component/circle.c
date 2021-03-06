#include "../component/circle.h"
#include "../util/util.h"

void MoveCircleToVector(Circle *circle, const Vector *vector) {
    circle->center = vector;
}

// https://mathworld.wolfram.com/Circle-CircleIntersection.html
bool IntersectsCircle(const Circle *circle, const Circle *otherCircle) {
    return (GetVectorDistance(circle->center, otherCircle->center)) < (circle->radius + otherCircle->radius);
}

// Derived from: (x - xc)^2 + (y - yc)^2 < radius^2
bool CircleContainsVector(const Circle *circle, const Vector* vector) {
    return IsLesserThanOrEqual((GetVectorDistance(circle->center, vector)), circle->radius);
}

bool AreEqualCircles(const Circle *circle, const Circle *otherCircle) {
    return ((AreEqualVectors(circle->center, otherCircle->center)) && (IsEqual(circle->radius, otherCircle->radius)));
}

Circle * CreateCircleFromPoints(
    float x0, float y0, float radius,
    int xv, int yv, int collisionLayer, 
    const unsigned int color, bool fill) 
    {
        Vector *center = CreateVector(x0, y0);
        return CreateCircle(center, radius, xv, yv, collisionLayer, color, fill);
}

Circle * CreateCircle(
    Vector *center, float radius,
    int xv, int yv, int collisionLayer,
    const unsigned int color, bool fill) 
    {
        ShapeRules *rules = CreateNewShapeRule(xv, yv, collisionLayer);
        Circle *circle = (Circle*)AllocMem(sizeof(Circle));
        circle->center = center;
        circle->radius = radius;
        circle->rules = rules;
        circle->color = color;
        circle->fill = fill;
        return circle;
}
