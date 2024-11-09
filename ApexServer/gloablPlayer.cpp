//
// Created by Administrator on 2024/11/3.
//

#include "Player.h"
GlobalPlayer::GlobalPlayer(const int index) {
    const uint64_t playerAddr = mem.OFF_BASE + OFF_ENTITY_LIST + ((static_cast<unsigned long long>(index) + 1) << 5);
    basePtr = mem.Read<uint64_t>(playerAddr);
    if(basePtr == 0) {
        SPDLOG_ERROR("basePtr is null");
    }
}

void GlobalPlayer::read() {
    struct ReadRequest {
        uint64_t offset;
        void *buffer;
        size_t size;
    };
    char nameBuffer[8] = {0};
    handle = mem.CreateScatterHandle();
    if(handle == nullptr) {
        SPDLOG_ERROR("Failed to create scatter handle");
    }
    std::vector<ReadRequest> initialRequests = {
        {OFF_TEAM_NUMBER, &team, sizeof(team)},
        {OFF_NAME, &nameBuffer, sizeof(nameBuffer)},
        {OFF_LIFE_STATE, &isDead, sizeof(isDead)},
        {OFF_BLEEDOUT_STATE,&isKnocked,sizeof(isKnocked)},
        {OFF_GLOW_ENABLE, &glowEnable, sizeof(glowEnable)},
        {OFF_GLOW_THROUGH_WALL, &glowThroughWall,sizeof(glowThroughWall)},
        {OFF_GLOW_HIGHLIGHT_ID, &highlightID, sizeof(highlightID)},
    };
    for (const auto &[offset, buffer, size]: initialRequests) {
        const uint64_t address = basePtr + offset;
        mem.AddScatterReadRequest(handle, address, buffer, size);
        if(buffer == nullptr) {
            SPDLOG_ERROR("req.buffer is null");
        }
    }
    mem.ExecuteReadScatter(handle);
    name = nameBuffer;
    mem.CloseScatterHandle(handle);
}
