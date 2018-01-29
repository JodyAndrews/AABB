#ifndef AABB_VEC2_H
#define AABB_VEC2_H

#include <stdbool.h>

#define VEC2ZERO { .x = 0, .y = 0 }
#define VEC2ONE { .x = 1, .y = 1 }

typedef struct {
  double x;
  double y;
} vec2;

///
/// \param a
/// \param b
/// \return
double mVec2EncAngle(vec2 a, vec2 b);

/// Tests if two vector 2s are equal
/// \param a
/// \param b
/// \return true if equal, otherwise false
bool mVec2Equal(vec2 a, vec2 b);

/// Test if two vectors are parallel
/// \param a
/// \param b
/// \return
bool mVec2Parallel(vec2 a, vec2 b);

/// Projects a vector onto another
/// \param v
/// \param onto
/// \return resulting vector
vec2 mVec2Proj(vec2 v, vec2 onto);

/// The dot product of two vector 2s
/// \param a
/// \param b
/// \return dot product as double
double mVec2Dot(vec2 a, vec2 b);

/// Changes the direction of a vector to it's opposite
/// \param v
/// \return negated vector
vec2 mVec2Neg(vec2 v);

/// Unit vector of a vec 2
/// \param v
/// \return vec2 unit
vec2 mVec2Unit(vec2 v);

/// Returns the length of a vector2
/// \param v
/// \return length of vec2
double mVec2Len(vec2 v);

/// Multiplies a vector by a scale
/// \param v
/// \param s
/// \return result of multiplication
vec2 mVec2Mul(vec2 v, double s);

/// Divides a vector by scale
/// \param v
/// \param s
/// \return result of division
vec2 mVec2Div(vec2 v, double s);

/// Changes vector 2 values to absolutes
/// \param v
/// \return
vec2 mVec2Fabs(vec2 v);

/// Rotates a vector around it's center
/// \param v
/// \param deg
/// \return rotated vector
vec2 mVec2Rot(vec2 v, double deg);

/// Rotates a vector by 90 degrees
/// \param v
/// \return
vec2 mVec2Rot90(vec2 v);

/// Rotates a vector by 180 degrees
/// \param v
/// \return
vec2 mVec2Rot180(vec2 v);

/// Rotates a vector by 270 degrees
/// \param v
/// \return
vec2 mVec2Rot270(vec2 v);

/// Sum two Vector2s together
/// \param vec_a
/// \param vec_b
/// \return Sum of the source vectors
vec2 mVec2Add(vec2 vec_a, vec2 vec_b);

/// Subtracts two vector2s
/// \param vec_a
/// \param vec_b
/// \return Result of subtraction
vec2 mVec2Sub(vec2 vec_a, vec2 vec_b);

/// Inverse values for x and y of a vector 2
/// \param vec
/// \return Result of inverse
vec2 mVec2Inv(vec2 vec);

#endif //AABB_VEC2_H
