#include <stdlib.h>
#include <math.h>
#include "aabb.h"
#include "include/common.h"

vec2 cVec2Fabs(vec2 v)
{
    v.x = (float)fabs(v.x);
    v.y = (float)fabs(v.y);
    return v;
}

vec2 cVec2Zero()
{
    vec2 zero;
    zero.x = 0;
    zero.y = 0;
    return zero;
}

vec2 cAddVec2(vec2 vec_a, vec2 vec_b)
{
    vec_a.x += vec_b.x;
    vec_a.y += vec_b.y;
    return vec_a;
}

vec2 cSubVec2(vec2 vec_a, vec2 vec_b)
{
    vec_a.x -= vec_b.x;
    vec_a.y -= vec_b.y;
    return vec_a;
}

vec2 cAABBBottomLeft(aabb *self)
{
    vec2 bldv = cVec2Zero();
    bldv.x = -self->he.x;
    bldv.y = self->he.y;
    return cAddVec2(self->center, bldv);
}

vec2 cAABBTopLeft(aabb *self)
{
    vec2 tldv = cVec2Zero();
    tldv.x = -self->he.x;
    tldv.y = -self->he.y;
    return cAddVec2(self->center, tldv);
}

vec2 cAABBTopRight(aabb *self)
{
    vec2 trdv = cVec2Zero();
    trdv.x = self->he.x;
    trdv.y = -self->he.y;
    return cAddVec2(self->center, trdv);
}

vec2 cAABBBottomRight(aabb *self)
{
    return cAddVec2(self->center, self->he);
}

enum cBOOL cAABBOverlap(aabb *self, aabb *aabb)
{
    vec2 cd = aabb->center;
    cd = cSubVec2(cd, self->center);
    // Todo: For consideration. Potential minor precision loss here, from float to double
    cd = cVec2Fabs(cd);

    vec2 hes = self->he;
    hes = cAddVec2(hes, aabb->he);

    cd = cSubVec2(cd, hes);
    return cd.x < 0 && cd.y < 0 ? cTRUE : cFALSE;
}

enum cBOOL cAABBContainsPoint(aabb *self, vec2 p)
{
    // Todo: For consideration. Potential minor precision loss here, from float to double
    vec2 d = cVec2Fabs(cSubVec2(p, self->center));
    return d.x < self->he.x && d.y < self->he.y ? cTRUE : cFALSE;
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