//
// Created by Administrator on 2024/11/3.
//
#include "Player.h"

LocalPlayer::LocalPlayer() {
    const uint64_t localPlayerAddr = mem.OFF_BASE + OFF_LOCAL_PLAYER;
    basePtr = mem.Read<uint64_t>(localPlayerAddr);
    if (basePtr == 0) {
        SPDLOG_ERROR("basePtr is null");
    }
}

void LocalPlayer::read() {
    struct ReadRequest {
        uint64_t offset;
        void *buffer;
        size_t size;
    };
    handle = mem.CreateScatterHandle();
    if (handle == nullptr)
        SPDLOG_ERROR("get handle failed.");
    std::vector<ReadRequest> initialRequests = {
        {OFF_LIFE_STATE, &isDead, sizeof(isDead)},
        {OFF_BLEEDOUT_STATE, &isKnocked, sizeof(isKnocked)},
        {OFF_ZOOMING, &isZoom, sizeof(isZoom)},
        {OFF_TEAM_NUMBER, &team, sizeof(team)},
        {OFF_LOCAL_ORIGIN, &localOrigin, sizeof(localOrigin)},
        {OFF_CAMERAORIGIN, &cameraPosition, sizeof(cameraPosition)},
        {OFF_VIEW_ANGLES, &viewAngles, sizeof(viewAngles)},
        {OFF_YAW, &viewYaw, sizeof(viewYaw)}
    };
    for (const auto &[offset, buffer, size]: initialRequests) {
        const uint64_t address = basePtr + offset;
        mem.AddScatterReadRequest(handle, address, buffer, size);
        if (buffer == nullptr) {
            SPDLOG_ERROR("buffer is null");
        }
    }
    mem.ExecuteReadScatter(handle);
    mem.CloseScatterHandle(handle);
}
