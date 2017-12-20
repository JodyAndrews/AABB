#include <stdlib.h>
#include <math.h>
#include "aabb.h"
#include "include/common.h"

vec2 cVec2Fabs(vec2 v)
{
    v.x = fabs(v.x);
    v.y = fabs(v.y);
    return v;
}

vec2 cVec2Zero()
{
    vec2 zero;
    zero.x = 0;
    zero.y = 0;
    return zero;
}

vec2 cVec2Add(vec2 vec_a, vec2 vec_b)
{
    vec_a.x += vec_b.x;
    vec_a.y += vec_b.y;
    return vec_a;
}

vec2 cVec2Sub(vec2 vec_a, vec2 vec_b)
{
    vec_a.x -= vec_b.x;
    vec_a.y -= vec_b.y;
    return vec_a;
}

vec2 cVec2Inverse(vec2 vec)
{
    vec.x = 1/vec.x;
    vec.y = 1/vec.y;
    return vec;
}

vec2 cAABBBottomLeft(aabb *self)
{
    vec2 bldv = cVec2Zero();
    bldv.x = -self->he.x;
    bldv.y = self->he.y;
    return cVec2Add(self->center, bldv);
}

vec2 cAABBTopLeft(aabb *self)
{
    vec2 tldv = cVec2Zero();
    tldv.x = -self->he.x;
    tldv.y = -self->he.y;
    return cVec2Add(self->center, tldv);
}

vec2 cAABBTopRight(aabb *self)
{
    vec2 trdv = cVec2Zero();
    trdv.x = self->he.x;
    trdv.y = -self->he.y;
    return cVec2Add(self->center, trdv);
}

vec2 cAABBBottomRight(aabb *self)
{
    return cVec2Add(self->center, self->he);
}

enum cBOOL cAABBOverlap(aabb *self, aabb *aabb, vec2 *intersection)
{
    vec2 cd = cVec2Fabs(cVec2Sub(aabb->center, self->center));

    vec2 hes = self->he;
    hes = cVec2Add(hes, aabb->he);

    intersection->x = cd.x - hes.x;
    intersection->y = cd.y - hes.y;

    return intersection->x < 0 && intersection->y < 0 ? cTRUE : cFALSE;
}

enum cBOOL cAABBContainsPoint(aabb *self, vec2 p)
{
    vec2 d = cVec2Fabs(cVec2Sub(p, self->center));
    return d.x < self->he.x && d.y < self->he.y ? cTRUE : cFALSE;
}

void cAABBScale(aabb *self, vec2 scale)
{
    self->he.x *= scale.x;
    self->he.y *= scale.y;
}

aabb *cInitAABB(vec2 c, vec2 he)
{
    aabb *naabb = (aabb*)malloc(sizeof(aabb));
    naabb->center = c;
    naabb->he = he;

    naabb->bottomLeft = cAABBBottomLeft;
    naabb->topLeft = cAABBTopLeft;
    naabb->topRight = cAABBTopRight;
    naabb->bottomRight = cAABBBottomRight;
    naabb->overlaps = cAABBOverlap;
    naabb->containsPoint = cAABBContainsPoint;
    return naabb;
}