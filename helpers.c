#include <math.h>
#include <float.h>
#include "helpers.h"

/// Convert degrees to radians
/// \param degrees
/// \return radians
double mDeg2Rad(double degrees)
{
  return degrees * pi / 180.0f;
}

/// Clamps a double
/// \param x
/// \param min
/// \param max
/// \return clamped double
double dClamp(double x, double min, double max)
{
  if (x < min) {
    return min;
  }

  if (max < x) {
    return max;
  }

  return x;
}

/// Check if two doubles are equal
/// \param a
/// \param b
/// \return true if equal otherwise false
bool dEqual(double a, double b)
{
  return fabs(a - b) < DBL_EPSILON;
}
