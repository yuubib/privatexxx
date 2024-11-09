//
// Created by Administrator on 2024/11/3.
//
#include "Glow.h"

Glow::Glow() {
    uint64_t highlightSettingsPointerAddr = mem.OFF_BASE + OFF_GLOW_HIGHLIGHTS;
    highlightSettingsPtr = mem.Read<uint64_t>(highlightSettingsPointerAddr, true);
    if (highlightSettingsPtr == NULL) {
        SPDLOG_ERROR("Highlight settings pointer is invalid");
    }
}


void Glow::setCustomGlow() const {
    if (!mem.IsValidPointer(globalPlayer->basePtr)) {
        SPDLOG_ERROR("player's base pointer is invalid");
        return;
    }
    constexpr unsigned char settingIndex = 65;
    float glowColor[3] = {1, 0, 0};
    if (globalPlayer->glowEnable) {
        const uint64_t glowEnableAddr = globalPlayer->basePtr + OFF_GLOW_ENABLE;
        const uint64_t glowThroughWallAddr = globalPlayer->basePtr + OFF_GLOW_THROUGH_WALL;
        mem.Write<int>(glowEnableAddr, globalPlayer->glowEnable);
        mem.Write<int>(glowThroughWallAddr, globalPlayer->glowThroughWall);
    }
    const uint64_t highlightIdAddr = globalPlayer->basePtr + OFF_GLOW_HIGHLIGHT_ID;
    mem.Write<unsigned char>(highlightIdAddr, settingIndex);
    const uint64_t glowFixAddr = globalPlayer->basePtr + OFF_GLOW_FIX;
    mem.Write<uint64_t>(glowFixAddr, settingIndex);
}

void Glow::setHighlightSettings() {
    int InvisibleIndex = 65; // Invis
    int VisibleIndex = 70; // Vis
    std::vector<unsigned char> highlightFunctionBits = {
        109, // InsideFunction							2
        6, // OutlineFunction: HIGHLIGHT_OUTLINE_OBJECTIVE			125
        64, // OutlineRadius: size * 255 / 8				64
        64 // (EntityVisible << 6) | State & 0x3F | (AfterPostProcess << 7) 	64
    };
    std::vector<float> invisibleGlowColorRGB = {0, 1, 0};
    std::vector<float> visibleGlowColorRGB = {1, 0, 0};

    auto handle = mem.CreateScatterHandle();

    mem.AddScatterWriteRequest(handle, highlightSettingsPtr + OFF_GLOW_HIGHLIGHT_TYPE_SIZE * InvisibleIndex + 0x0,
                               &highlightFunctionBits, sizeof(highlightFunctionBits));
    mem.AddScatterWriteRequest(handle, highlightSettingsPtr + OFF_GLOW_HIGHLIGHT_TYPE_SIZE * InvisibleIndex + 0x4,
                               &invisibleGlowColorRGB, sizeof(invisibleGlowColorRGB));

    // Visible
    mem.AddScatterWriteRequest(handle, highlightSettingsPtr + OFF_GLOW_HIGHLIGHT_TYPE_SIZE * VisibleIndex + 0x0,
                               &highlightFunctionBits, sizeof(highlightFunctionBits));
    mem.AddScatterWriteRequest(handle, highlightSettingsPtr + OFF_GLOW_HIGHLIGHT_TYPE_SIZE * VisibleIndex + 0x4,
                               &visibleGlowColorRGB, sizeof(visibleGlowColorRGB));

    mem.ExecuteWriteScatter(handle);
    mem.CloseScatterHandle(handle);
}
