//
// Created by Administrator on 2024/11/4.
//

#include "camera.h"

#include "spdlog/spdlog.h"

Camera::Camera() {
    screenSize.x = 2560;
    screenSize.y = 1440;
    screenCenter = {screenSize.x / 2, screenSize.y / 2};
    const uint64_t cameraRenderPointerAddress = mem.OFF_BASE + OFF_VIEWRENDER;
    renderPtr = mem.Read<uint64_t>(cameraRenderPointerAddress);
    if(renderPtr == 0) {
        SPDLOG_ERROR("renderPtr is null");
    }
}
bool Camera::worldToScreen(Vector3D worldPosition, Vector2D& screenPosition) const {
    Vector3D transformed = viewMatrix.Transform(worldPosition);
    if (transformed.z < 0.001) {
        return false;
    }

    transformed.x *= 1.0 / transformed.z;
    transformed.y *= 1.0 / transformed.z;

    if (transformed.x < -1.05f || transformed.x > 1.05f || transformed.y < -1.05f || transformed.y > 1.05f) {
        return false;
    }

    screenPosition = Vector2D(screenSize.x / 2.0f + transformed.x * (screenSize.x / 2.0f), screenSize.y / 2.0f - transformed.y * (screenSize.y / 2.0f));
    return true;
}

void Camera::update() {
    const auto matrixPtr = mem.Read<uint64_t>(renderPtr + OFF_VIEWMATRIX, true);
    viewMatrix = mem.Read<ViewMatrix>(matrixPtr);
}