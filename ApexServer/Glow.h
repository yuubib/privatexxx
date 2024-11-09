#pragma once
#include <cstdint>
#include "Memory/Memory.h"
#include "Player.h"

class Glow {
public:
    std::byte bodyStyle, borderStyle, borderWidth, transparency;

    Glow();

    std::shared_ptr<LocalPlayer> localPlayer;
    std::shared_ptr<GlobalPlayer> globalPlayer;
    uint64_t highlightSettingsPtr = {};
    void setGlowMode(int x_val, int y_val, int z_val, int transparency_val) {
        bodyStyle = static_cast<std::byte>(x_val);
        borderStyle = static_cast<std::byte>(y_val);
        borderWidth = static_cast<std::byte>(z_val);
        transparency = static_cast<std::byte>(transparency_val);
    }

    void setGlowMode(std::byte x_val, std::byte y_val, std::byte z_val, std::byte transparency_val) {
        bodyStyle = x_val;
        borderStyle = y_val;
        borderWidth = z_val;
        transparency = transparency_val;
    }

    void setCustomGlow() const;

    void setHighlightSettings();
};
