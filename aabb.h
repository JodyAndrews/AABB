#ifndef AABB_H
#define AABB_H

#include "stdbool.h"
#include "vec2.h"

/// AABB Struct
typedef struct  {
  /// Center of AABB
  vec2 center;

  /// Half-Extents of AABB
  vec2 he;
} aabb;

/// Clamps a vector2 to an AABB
/// \param a
/// \param p
/// \return clamped vec2
vec2 mAABBClampVec2(aabb *a, vec2 p);

/// Bottom Left of the AABB
/// \param aabb
/// \return Vector2 of the Bottom Left of the AABB
vec2 mAABBBottomLeft(aabb *a);

/// Top Left of the AABB
/// \param aabb
/// \return Vector2 of the Top Left of the AABB
vec2 mAABBTopLeft(aabb *a);

/// Top Right of the AABB
/// \param aabb
/// \return Vector2 of the Top Right of the AABB
vec2 mAABBTopRight(aabb *a);

/// Bottom Right of the AABB
/// \param aabb
/// \return Vector2 of the Bottom Right of the AABB
vec2 mAABBBottomRight(aabb *a);

/// Left-most (x) point on AABB
/// \param a
/// \return
double mAABBLeft(aabb *a);

/// Top-most (y) point on AABB
/// \param a
/// \return
double mAABBTop(aabb *a);

/// Right-most (x) point on AABB
/// \param a
/// \return
double mAABBRight(aabb *a);

/// Bottom-most (y) point on AABB
/// \param a
/// \return
double mAABBBottom(aabb *a);

/// Retrieves the intersection depth as an AABB of two AABBs
/// \param a
/// \param b
/// \param intersection result
void mAABBIntersection(aabb *a, aabb *b, aabb *intersection);

/// Tests for an Overlap between two AABBs.
/// \param a
/// \param b
/// \return cTRUE when an overlap occurs, otherwise cFALSE. Will return cFALSE if vector boundaries overlap.
bool mAABBOverlap(aabb *a, aabb *b, vec2 *intersection);

/// Tests for a point (vec2) within the AABB
/// \param a
/// \param b
/// \return true when point is inside AABB, otherwise false.
bool mAABBContainsPoint(aabb *a, vec2 p);

/// Scales an AABB via a vector2
/// \param self
/// \param scale
void mAABBScale(aabb *self, vec2 scale);

/// Stretches an AABB in the direction of a vector2
/// \param a
/// \param stretch
void mAABBStretch(aabb *a, vec2 stretch);

/// Unions two AABBs into one bounding AABB
/// \param a
/// \param b
/// \param res
void mAABBUnion(aabb *a, aabb *b, aabb *res);

/// Creates an AABB from a center vector and it's halfextents
/// \param c
/// \param he
/// \return
aabb *mInitAABB(vec2 c, vec2 he);

#endif //AABB_H