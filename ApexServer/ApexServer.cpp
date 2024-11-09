// ApexServer.cpp: 定义应用程序的入口点。
//

#include "ApexServer.h"
#include "Memory/Memory.h"
#include <memory>
#include <spdlog/spdlog.h>
#include "Player.h"
#include "Glow.h"
#include "camera.h"
#include <vector>

using namespace std;

int main() {
	if (!mem.Init("r5apex.exe", true, false)) {
		SPDLOG_ERROR("mem init failed.");
		return 0;
	}
	std::shared_ptr<LocalPlayer> player = std::make_shared<LocalPlayer>();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	std::shared_ptr<Glow> glow = std::make_shared<Glow>();

	std::vector<std::shared_ptr<GlobalPlayer>> players;

	for(int i = 0; i < 70; i++) {
		players.push_back(std::make_shared<GlobalPlayer>(i));
	}
	return 0;
}
