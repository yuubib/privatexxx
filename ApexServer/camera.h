#pragma once
#include "Memory/Memory.h"
#include "vector2.hpp"
#include "vector3.hpp"
#include "offset.h"
#include "matrix.hpp"
class Camera {
public:
    Vector2D screenSize{};
    Vector2D screenCenter{};
    uint64_t renderPtr;
    Camera();
    bool worldToScreen(Vector3D worldPosition, Vector2D &screenPosition) const;

    void update();

    ViewMatrix viewMatrix{};
};
