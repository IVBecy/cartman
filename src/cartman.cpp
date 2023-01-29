#include <windows.h>
#include <vector>

#include "../headers/vars.h"
#include "../headers/cheatFunctions.h"
#include "./gui/gui.h"
#include "config.h"


int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previousInstance, PWSTR arguments, int commandShow){
    
    // Cheat classes initialisation
    Glows GlowCheats;
    Misc MiscCheats;
    Aim AimCheats;
   
    // Get process and modules
    int proc_id = MemMan.getPid(L"csgo.exe");
    val.clientModule = MemMan.getModule(proc_id,L"client.dll");
    val.engineModule = MemMan.getModule(proc_id, L"engine.dll");
    val.localPlayer = MemMan.ReadMem<uintptr_t>(val.clientModule + offset.dwLocalPlayer);
    val.localPlayer = MemMan.ReadMem<uintptr_t>(val.clientModule + offset.dwLocalPlayer);

    // Game vars
    uintptr_t glowObj = MemMan.ReadMem<uintptr_t>(val.clientModule + offset.dwGlowObjectManager);
    int team = MemMan.ReadMem<int>(val.localPlayer + offset.m_iTeamNum);

    // Menu
    gui::CreateHWindow("Cartman", "Cartman");
    gui::CreateDevice();
    gui::CreateImGui();

    // {anic
    while(gui::exit){

        if (GetAsyncKeyState(VK_END)) {
            exit(1);
        }
        
        gui::BeginRender();
        gui::Render();
        gui::EndRender();

        // Toggle functions
        if (config::toggle_bhop) {
            MiscCheats.bunnyHop();
        }
        if (config::toggle_flash) {
            MiscCheats.antiFlash();
        }
        if (config::toggle_rcs) {
            Vector2 oldRecoil;
            AimCheats.recoil(oldRecoil);
        }

        // Entity loop
        for (int i = 0; i < 64; i++){
            uintptr_t entity = MemMan.ReadMem<uintptr_t>(val.clientModule + offset.dwEntityList + i * 0x10);
            if (entity != 0){

                int entityHealth = MemMan.ReadMem<int>(entity + offset.m_iHealth);
                int glowIndex = MemMan.ReadMem<int>(entity + offset.m_iGlowIndex);
                int enitityTeam = MemMan.ReadMem<int>(entity + offset.m_iTeamNum);

                if (team == enitityTeam) { continue; }
                else {
                    if (config::toggle_glow){
                        std::vector<float>glowColours{ config::colours[0],config::colours[1] ,config::colours[2] };
                        GlowCheats.glowHack(entity,glowObj, glowIndex,entityHealth, config::health_based, glowColours);
                    }
                    if (config::toggle_chams) {
                        std::vector<float>chamsColours{ config::chams_colours[0],config::chams_colours[1],config::chams_colours[2] };
                        GlowCheats.chams(entity, chamsColours, config::chams_brightness);
                    }
                    if (config::toggle_trigger) {
                        if (!AimCheats.Trigger(team, enitityTeam)) { continue; }
                    }
                    if (config::toggle_aim) {
                        if(AimCheats.aimBot(entity, config::aimbot_snap, config::aimbot_fov)) { continue; };
                    }
            }
            MemMan.WriteMem<bool>(glowObj + ((glowIndex * 0x38) + 0x28), true);
            MemMan.WriteMem<bool>(glowObj + ((glowIndex * 0x38) + 0x29), false);
            }
        }
    }

    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();
    return 0;
}