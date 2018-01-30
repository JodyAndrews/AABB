#include <math.h>
#include "vec2.h"
#include "helpers.h"

///
/// \param a
/// \param b
/// \return
double mVec2EncAngle(vec2 a, vec2 b)
{
  vec2 unit_a = mVec2Unit(a);
  vec2 unit_b = mVec2Unit(b);
  double dp = mVec2Dot(unit_a, unit_b);
  return mDeg2Rad(acos(dp));
}

/// Tests if two vector 2s are equal
/// \param a
/// \param b
/// \return true if equal, otherwise false
bool mVec2Equal(vec2 a, vec2 b)
{
  return dEqual(a.x - b.x, 0) && dEqual(a.y - b.y, 0);
}

/// Test if two vectors are parallel
/// \param a
/// \param b
/// \return
bool mVec2Parallel(vec2 a, vec2 b)
{
  vec2 na = mVec2Rot90(a);

  return dEqual(0, mVec2Dot(na, b));
}

/// Projects a vector onto another
/// \param v
/// \param onto
/// \return resulting vector
vec2 mVec2Proj(vec2 v, vec2 onto)
{
  double d = mVec2Dot(onto, onto);

  if (0 < d)
  {
    double dp = mVec2Dot(v, onto);
    return mVec2Mul(onto, dp / d);
  }

  return onto;
}

/// The dot product of two vector 2s
/// \param a
/// \param b
/// \return dot product as double
double mVec2Dot(vec2 a, vec2 b)
{
  return a.x * b.x + a.y * b.y;
}

/// Changes the direction of a vector to it's opposite
/// \param v
/// \return negated vector
vec2 mVec2Neg(vec2 v)
{
  v.x = -v.x;
  v.y = -v.y;
  return v;
}

/// Unit vector of a vec 2
/// \param v
/// \return vec2 unit
vec2 mVec2Unit(vec2 v)
{
  double len = mVec2Len(v);
  if (0 < len) {
    return mVec2Div(v,len);
  }

  return v;
}

/// Returns the length of a vector2
/// \param v
/// \return length of vec2
double mVec2Len(vec2 v)
{
  return sqrt(v.x * v.x + v.y * v.y);
}

/// Multiplies a vector by a scale
/// \param v
/// \param s
/// \return result of multiplication
vec2 mVec2Mul(vec2 v, double s)
{
  v.x *= s;
  v.y *= s;
  return v;
}

/// Divides a vector by scale
/// \param v
/// \param s
/// \return result of division
vec2 mVec2Div(vec2 v, double s)
{
  v.x /= s;
  v.y /= s;
  return v;
}

/// Changes vector 2 values to absolutes
/// \param v
/// \return
vec2 mVec2Fabs(vec2 v)
{
  v.x = fabs(v.x);
  v.y = fabs(v.y);
  return v;
}

/// Rotates a vector around it's center
/// \param v
/// \param deg
/// \return rotated vector
vec2 mVec2Rot(vec2 v, double deg)
{
  double rad = mDeg2Rad(deg);
  double sine = sin(rad);
  double cosine = cos(rad);
  vec2 v2;
  v2.x = v.x * cosine - v.y * sine;
  v2.y = v.y * cosine + v.x * sine;
  return v2;
}

/// Rotates a vector around it's center by 90 degrees
/// \param v
/// \return
vec2 mVec2Rot90(vec2 v)
{
  vec2 r;
  r.x = -v.y;
  r.y = v.x;
  return r;
}

/// Rotates a vector by 180 degrees
/// \param v
/// \return
vec2 mVec2Rot180(vec2 v)
{
  return mVec2Neg(v);
}

/// Rotates a vector by 270 degrees
/// \param v
/// \return
vec2 mVec2Rot270(vec2 v)
{
  vec2 r = { v.y, -(v.x) };
  return r;
}

/// Sum two Vector2s together
/// \param vec_a
/// \param vec_b
/// \return Sum of the source vectors
vec2 mVec2Add(vec2 vec_a, vec2 vec_b)
{
  vec_a.x += vec_b.x;
  vec_a.y += vec_b.y;
  return vec_a;
}

/// Subtracts two vector2s
/// \param vec_a
/// \param vec_b
/// \return Result of subtraction
vec2 mVec2Sub(vec2 vec_a, vec2 vec_b)
{
  vec_a.x -= vec_b.x;
  vec_a.y -= vec_b.y;
  return vec_a;
}

/// Inverse values for x and y of a vector 2
/// \param vec
/// \return Result of inverse
vec2 mVec2Inv(vec2 vec)
{
  vec.x = vec.x == 0 ? 0 : 1/vec.x;
  vec.y = vec.y == 0 ? 0 : 1/vec.y;
  return vec;
}