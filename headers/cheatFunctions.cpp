#include  "cheatFunctions.h"
#include "vars.h"

/*=============================================================================================================================================*/
/*=================================================================GLOW HACKS==================================================================*/
/*=============================================================================================================================================*/


// Glow Esp
void Glows::glowHack(uintptr_t entity, uintptr_t glow_obj, int glowIndex, int health, bool hBased, std::vector<float>colours) {
    MemMan.WriteMem<glowEnemy>(glow_obj + (glowIndex * 0x38) + 0x8, hpGlow(health, hBased, colours));
}

// Chams 
void Glows::chams(uintptr_t entity, std::vector<float>& colours, float brightness) {
    // Colours
    chamsColour entColour{ };
    entColour.red = 255 * (int)colours[0];
    entColour.green = 255 * (int)colours[1];
    entColour.blue = 255 * (int)colours[2];
    MemMan.WriteMem<chamsColour>(entity + offset.m_clrRender, entColour);
    // Brightness
    uintptr_t _this = static_cast<uintptr_t>(val.engineModule + offset.model_ambient_min - 0x2c);
    MemMan.WriteMem<int32_t>(val.engineModule + offset.model_ambient_min, *reinterpret_cast<uintptr_t*>(&brightness) ^ _this);
}


/*=============================================================================================================================================*/
/*=================================================================AIM HACKS===================================================================*/
/*=============================================================================================================================================*/


// Trigger Bot
int Aim::Trigger(int team, int myTeam) {

    // Main vars
    int crosshair = MemMan.ReadMem<int>(val.localPlayer + offset.m_iCrosshairId);
    uintptr_t player = MemMan.ReadMem<uintptr_t>(val.clientModule + offset.dwEntityList + (crosshair - 1) * 0x10);
    uintptr_t entity = MemMan.ReadMem<uintptr_t>(val.clientModule + offset.dwEntityList + crosshair * 0x10);

    // Check
    if (!crosshair || crosshair > 64) { return 0; };
    if (team == myTeam) { return 0; }


    // Write to mem
    MemMan.WriteMem<uintptr_t>(val.clientModule + offset.dwForceAttack, 5);
    Sleep(20);
    MemMan.WriteMem<uintptr_t>(val.clientModule + offset.dwForceAttack, 4);
    return 1;
}


// Recoil control
void Aim::recoil(Vector2& oldPunch) {
    // Offset based vars
    int shotsFired = MemMan.ReadMem<int>(val.localPlayer + offset.m_iShotsFired);
    uintptr_t clientState = MemMan.ReadMem<uintptr_t>(val.engineModule + offset.dwClientState);
    Vector2 clientStateViewAngles = MemMan.ReadMem<Vector2>(clientState + offset.dwClientState_ViewAngles);
    Vector2 aimPunch = MemMan.ReadMem<Vector2>(val.localPlayer + offset.m_aimPunchAngle);

    // Calculated vars
    Vector2 recoilVec{
    clientStateViewAngles.x + oldPunch.x - aimPunch.x * 2.f,
    clientStateViewAngles.y + oldPunch.y - aimPunch.y * 2.f
    };

    // Error check
    if (recoilVec.x > 89.f) {
        recoilVec.x = 89.f;
    }
    if (recoilVec.x < -89.f) {
        recoilVec.x = -89.f;
    }
    while (recoilVec.y > 180.f) {
        recoilVec.y -= 360.f;
    }
    while (recoilVec.y < -180.f) {
        recoilVec.y += 360.f;
    }
    // Write to mem
    MemMan.WriteMem<Vector2>(clientState + offset.dwClientState_ViewAngles, recoilVec);
    oldPunch.x = aimPunch.x * 2.f;
    oldPunch.y = aimPunch.y * 2.f;
}


// Aim Bot
int  Aim::aimBot(uintptr_t entity, float snap, float fov) {
    // Checks for irrelevant players
    if (MemMan.ReadMem<bool>(entity + offset.m_bDormant)) { return 0; }
    if (!MemMan.ReadMem<bool>(entity + offset.m_iHealth)) { return 0; }
    if (!MemMan.ReadMem<bool>(entity + offset.m_bSpottedByMask)) { return 0; }

    // Offset based vars
    Vector3 localEyePos = MemMan.ReadMem<Vector3>(val.localPlayer + offset.m_vecOrigin) + MemMan.ReadMem<Vector3>(val.localPlayer + offset.m_vecViewOffset);
    uintptr_t clientState = MemMan.ReadMem<uintptr_t>(val.engineModule + offset.dwClientState);
    Vector3 clientStateViewAngles = MemMan.ReadMem<Vector3>(clientState + offset.dwClientState_ViewAngles);
    Vector3 aimPunch = MemMan.ReadMem<Vector3>(val.localPlayer + offset.m_aimPunchAngle) * 2;
    uintptr_t boneMatrix = MemMan.ReadMem<uintptr_t>(entity + offset.m_dwBoneMatrix);
    Vector3 entityHead{
        MemMan.ReadMem<float>(boneMatrix + 0x30 * 8 + 0x0C),
        MemMan.ReadMem<float>(boneMatrix + 0x30 * 8 + 0x1C),
        MemMan.ReadMem<float>(boneMatrix + 0x30 * 8 + 0x2C),
    };

    // Calculated  vars
    Vector3 angle = CalculateAngle(localEyePos,entityHead, clientStateViewAngles + aimPunch);
    Vector3 newAngle = { };
    float calcFov =  std::hypot(angle.x, angle.y);

    // Checks
    if (calcFov < fov) {
        fov = calcFov;
        newAngle = angle;
    }

    if (!newAngle.IsZero()) {
        MemMan.WriteMem<Vector3>(clientState + offset.dwClientState_ViewAngles, clientStateViewAngles + newAngle / snap);
    }
    return 1;
}

/*=============================================================================================================================================*/
/*=================================================================MISC HACKS==================================================================*/
/*=============================================================================================================================================*/

// Bunny hop
void Misc::bunnyHop() {
    bool onGround = MemMan.ReadMem<bool>(val.localPlayer + offset.m_fFlags);
    if (GetAsyncKeyState(VK_SPACE) && onGround & (1 << 0)) {
        MemMan.WriteMem<BYTE>(val.clientModule + offset.dwForceJump, 6);
    }
}

// No flash
void Misc::antiFlash() {
    int flashTime = MemMan.ReadMem<int>(val.localPlayer + offset.m_flFlashDuration);
    if (flashTime > 0) {
        MemMan.WriteMem<int>(val.localPlayer + offset.m_flFlashDuration, 0);
    }
}