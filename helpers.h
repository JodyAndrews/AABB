
#ifndef AABB_HELPERS_H
#define AABB_HELPERS_H

#include <stdbool.h>

#define pi 3.14159265358979323846

/// Convert degrees to radians
/// \param degrees
/// \return radians
double mDeg2Rad(double degrees);

/// Clamps a double
/// \param x
/// \param min
/// \param max
/// \return clamped double
double dClamp(double x, double min, double max);

/// Check if two doubles are equal
/// \param a
/// \param b
/// \return true if equal otherwise false
bool dEqual(double a, double b);

#endif //AABB_HELPERS_H
