#include <stdlib.h>
#include "aabb.h"
#include "helpers.h"

/// Clamps a vector2 to an AABB
/// \param a
/// \param p
/// \return clamped vec2
vec2 mAABBClampVec2(aabb *a, vec2 p)
{
  vec2 clamp;

  clamp.x = dClamp(p.x, mAABBTopLeft(a).x, mAABBTopLeft(a).x + a->he.x * 2);
  clamp.y = dClamp(p.y, mAABBTopLeft(a).y, mAABBTopLeft(a).y + a->he.y * 2);

  return clamp;
}

/// Bottom Left of the AABB
/// \param aabb
/// \return Vector2 of the Bottom Left of the AABB
vec2 mAABBBottomLeft(aabb *a)
{
  vec2 bldv = VEC2ZERO;
  bldv.x = -a->he.x;
  bldv.y = a->he.y;
  return mVec2Add(a->center, bldv);
}

/// Top Left of the AABB
/// \param aabb
/// \return Vector2 of the Top Left of the AABB
vec2 mAABBTopLeft(aabb *a)
{
  vec2 tldv = VEC2ZERO;
  tldv.x = -a->he.x;
  tldv.y = -a->he.y;
  return mVec2Add(a->center, tldv);
}

/// Top Right of the AABB
/// \param a
/// \return Vector2 of the Top Right of the AABB
vec2 mAABBTopRight(aabb *a)
{
  vec2 trdv = VEC2ZERO;
  trdv.x = a->he.x;
  trdv.y = -a->he.y;
  return mVec2Add(a->center, trdv);
}

/// Bottom Right of the AABB
/// \param aabb
/// \return Vector2 of the Bottom Right of the AABB
vec2 mAABBBottomRight(aabb *a)
{
  return mVec2Add(a->center, a->he);
}

/// Tests for an Overlap between two AABBs.
/// \param a
/// \param b
/// \return cTRUE when an overlap occurs, otherwise cFALSE. Will return cFALSE if vector boundaries overlap.
bool mAABBOverlap(aabb *a, aabb *b, vec2 *intersection)
{
  vec2 cd = mVec2Fabs(mVec2Sub(b->center, a->center));

  vec2 hes = a->he;
  hes = mVec2Add(hes, b->he);

  intersection->x = cd.x - hes.x;
  intersection->y = cd.y - hes.y;

  return intersection->x < 0 && intersection->y < 0 ? true : false;
}

/// Tests for a point (vec2) within the AABB
/// \param a
/// \param b
/// \return true when point is inside AABB, otherwise false.
bool mAABBContainsPoint(aabb *self, vec2 p)
{
  vec2 d = mVec2Fabs(mVec2Sub(p, self->center));
  return d.x < self->he.x && d.y < self->he.y ? true : false;
}

/// Scales an AABB via a vector2
/// \param self
/// \param scale
void mAABBScale(aabb *self, vec2 scale)
{
  self->he.x *= scale.x;
  self->he.y *= scale.y;
}

/// Stretches an AABB in the direction of a vector2
/// \param a
/// \param stretch
void mAABBStretch(aabb *a, vec2 stretch)
{
  vec2 offset = mVec2Div(stretch, 2);

  a->center = mVec2Add(a->center, offset);
  a->he = mVec2Add(a->he, mVec2Fabs(offset));
}

aabb *mInitAABB(vec2 c, vec2 he)
{
  aabb *naabb = (aabb *) malloc(sizeof(aabb));
  naabb->center = c;
  naabb->he = he;

  return naabb;
}