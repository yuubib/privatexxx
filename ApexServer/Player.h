#pragma once
#include <cstdint>
#include "Memory/Memory.h"
#include "offset.h"
#include "spdlog/spdlog.h"
#include "vector3.hpp"
#include "vector2.hpp"
class Player {
public:
	virtual ~Player() = default;

	uint64_t basePtr{};
	VMMDLL_SCATTER_HANDLE handle;
    bool isDead{};
    bool isKnocked{};
    int team{};
	Player();
	virtual void read() = 0;
private:
};

class LocalPlayer final : public Player {
public:
	LocalPlayer();
	Vector3D localOrigin;
	Vector3D cameraPosition;
	Vector2D viewAngles;
	float viewYaw{};

	float zoomFOV{};
	float targetZoomFOV{};
	bool isZoom{};
	void read() override;
};

class GlobalPlayer final : public Player {
public:
	std::string name{};
	int glowEnable{};
	int glowThroughWall{};
	int highlightID{};
	explicit GlobalPlayer(int index);
	void read() override;
};
