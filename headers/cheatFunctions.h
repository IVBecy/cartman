#pragma once
#include <cstdint>
#include <vector>

#include "vectors.h"


// Glow cheats
class Glows {
public:
    // Glow Esp
    void glowHack(uintptr_t entity, uintptr_t glow_obj, int glowIndex, int health, bool hBased, std::vector<float>colours);
    // Chams
    void chams(uintptr_t entity, std::vector<float>& colours, float brightness);
};


// Aim related cheats
class Aim {
public:
    // Trigger Bot
    int Trigger(int team, int myTeam);
    // Recoil control
    void recoil(Vector2& oldPunch);
    // Rage Bot
    int aimBot(uintptr_t entity, float snap, float fov);
};


// Miscallenous options
class Misc {
public:
    // Bunny hop
    void bunnyHop();
    // No flash
    void antiFlash();
};
