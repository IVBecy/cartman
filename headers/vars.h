#pragma once
#include <cstdint>

#include "MemMan.h"
#include "vectors.h"
#include "csgo.h"

inline MemoryManagement MemMan;

// Data from the game
inline struct offset
{
	uintptr_t dwGlowObjectManager = signatures::dwGlowObjectManager;
	uintptr_t dwLocalPlayer = signatures::dwLocalPlayer;
	uintptr_t dwForceJump = signatures::dwForceJump;
	uintptr_t dwEntityList = signatures::dwEntityList;
	uintptr_t dwForceAttack = signatures::dwForceAttack;
	uintptr_t dwClientState_GetLocalPlayer = signatures::dwClientState_GetLocalPlayer;
	uintptr_t dwClientState_ViewAngles = signatures::dwClientState_ViewAngles;
	uintptr_t dwClientState = signatures::dwClientState;
	uintptr_t model_ambient_min = signatures::model_ambient_min;
	uintptr_t m_bDormant = signatures::m_bDormant;
	uintptr_t dwClientState_PlayerInfo = signatures::dwClientState_PlayerInfo;
	uintptr_t m_iGlowIndex = netvars::m_iGlowIndex;
	uintptr_t m_iTeamNum = netvars::m_iTeamNum;
	uintptr_t m_iHealth = netvars::m_iHealth;
	uintptr_t m_fFlags = netvars::m_fFlags;
	uintptr_t m_iCrosshairId = netvars::m_iCrosshairId;
	uintptr_t m_flFlashDuration = netvars::m_flFlashDuration;
	uintptr_t m_aimPunchAngle = netvars::m_aimPunchAngle;
	uintptr_t m_iShotsFired = netvars::m_iShotsFired;
	uintptr_t m_hActiveWeapon = netvars::m_hActiveWeapon;
	uintptr_t m_iItemDefinitionIndex = netvars::m_iItemDefinitionIndex;
	uintptr_t m_clrRender = netvars::m_clrRender;
	uintptr_t m_dwBoneMatrix = netvars::m_dwBoneMatrix;
	uintptr_t m_vecOrigin = netvars::m_vecOrigin;
	uintptr_t m_vecViewOffset = netvars::m_vecViewOffset;
	uintptr_t m_bSpottedByMask = netvars::m_bSpottedByMask;
	uintptr_t m_iObserverMode = netvars::m_iObserverMode;
	uintptr_t m_bIsDefusing = netvars::m_bIsDefusing;
	uintptr_t cl_grenadePreview = 0xe04C50;
} offset;

// Most used vars
inline struct vars
{
	uintptr_t localPlayer;
	uintptr_t clientModule;
	uintptr_t engineModule;
}val;

// Structure for making the enemy glow
struct glowEnemy
{
	float red;
	float green;
	float blue = 0.f;
	float alpha = 1.f;
	uint8_t padding[8];
	float unknown = 1.f;
	uint8_t padding2[4];
	BYTE occluded = true;
	BYTE unoccluded = false;
	BYTE bloom = false;
};

// Colorus for chams
struct chamsColour {
	int red;
	int green;
	int blue;
};

// Make enemies glow based on HP
inline glowEnemy hpGlow(int health,bool based,std::vector<float>colours) {
	if (based) {
		glowEnemy glowColour;
		glowColour.red = (float)(health * -0.01 + 1);
		glowColour.green = (float)(health * 0.01);
		return glowColour;
	}
	else {
		glowEnemy glowColour;
		glowColour.red = colours[0];
		glowColour.green = colours[1];
		glowColour.blue = colours[2];
		return glowColour;
	}
}

// Get distance between local player and entity
inline double getDistance(Vector3 localPos, Vector3 entityPos) {
	return sqrt(pow(localPos.x - entityPos.x, 2) + pow(localPos.y - entityPos.y, 2) + pow(localPos.z - entityPos.z, 2)) * 0.0254f;
}
