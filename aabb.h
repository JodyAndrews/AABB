#ifndef AABB_H
#define AABB_H

/// Struct : A Vec2
typedef struct struct_vec2 {
    float x;
    float y;
} vec2;

/// Struct: An AABB
typedef struct struct_aabb {
    vec2 center;
    vec2 he;

    // Function Pointers.
    // Note: Specifying any fp param is actually unnecessary but makes for (potentially) easier reading
    // and will also 'fix' syntax highlight in some IDEs

    /// Bottom Left of the AABB
    /// \param aabb
    /// \return Vector2 of the Bottom Left of the AABB
    vec2 (*bottomLeft)(struct struct_aabb *aabb);

    /// Top Left of the AABB
    /// \param aabb
    /// \return Vector2 of the Top Left of the AABB
    vec2 (*topLeft)(struct struct_aabb *aabb);

    /// Top Right of the AABB
    /// \param aabb
    /// \return Vector2 of the Top Right of the AABB
    vec2 (*topRight)(struct struct_aabb *aabb);

    /// Bottom Right of the AABB
    /// \param aabb
    /// \return Vector2 of the Bottom Right of the AABB
    vec2 (*bottomRight)(struct struct_aabb *aabb);
} aabb;

/// A zeroed Vector 2
/// \return Vector 2 with zeroed fields
vec2 cVec2Zero();

/// Sum two Vector2s together
/// \param vec_a
/// \param vec_b
/// \return Sum of the source vectors
vec2 cAddVec2(vec2 vec_a, vec2 vec_b);

/// Subtracts two vector2s
/// \param vec_a
/// \param vec_b
/// \return Result of subtraction
vec2 cSubVec2(vec2 vec_a, vec2 vec_b);

/// Creates an AABB from a center vector and it's halfextents
/// \param c
/// \param he
/// \return
aabb *cInitAABB(vec2 c, vec2 he);

#endif //AABB_H
