#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <cstdarg>
#include "vector.h"
#include <Windows.h>

// === Forward Declarations for Engine Interfaces ===
class IClientEntityList;
class IEngineTrace;
class IEngineClient;
class IMaterialSystem;
class IBaseClientDLL;
class IViewRender;
class IModelInfo;
class IModelRender;
class IMaterial;
class IInput;
class ISurface;
class CBaseEntity;
class C_BasePlayer;
struct model_t;

// === Forward Declarations for Internal Systems ===
class Game;
class Offsets;
class VR;
class Hooks;

// === Global Game Instance ===
inline Game* g_Game = nullptr;

// === Per-Player VR Info ===
struct Player
{
    C_BasePlayer* pPlayer = nullptr;
    bool isUsingVR = false;
    QAngle controllerAngle = { 0.f, 0.f, 0.f };
    Vector controllerPos = { 0.f, 0.f, 0.f };
    bool isMeleeing = false;
    bool isNewSwing = false;
    QAngle prevControllerAngle = { 0.f, 0.f, 0.f };
};

// === Game System ===
class Game
{
public:
    // Engine Interfaces
    IClientEntityList* m_ClientEntityList = nullptr;
    IEngineTrace* m_EngineTrace = nullptr;
    IEngineClient* m_EngineClient = nullptr;
    IMaterialSystem* m_MaterialSystem = nullptr;
    IBaseClientDLL* m_BaseClientDll = nullptr;
    //IViewRender* m_ClientViewRender = nullptr;
    //IViewRender* m_EngineViewRender = nullptr;
    IModelInfo* m_ModelInfo = nullptr;
    IModelRender* m_ModelRender = nullptr;
    IInput* m_VguiInput = nullptr;
    ISurface* m_VguiSurface = nullptr;

    // Module Bases
    uintptr_t m_BaseEngine = 0;
    uintptr_t m_BaseClient = 0;
    uintptr_t m_BaseServer = 0;
    uintptr_t m_BaseMaterialSystem = 0;
    uintptr_t m_BaseVgui2 = 0;

    // Core systems
    Offsets* m_Offsets = nullptr;
    VR* m_VR = nullptr;
    Hooks* m_Hooks = nullptr;

    bool m_Initialized = false;

    // VR player states
    std::array<Player, 24> m_PlayersVRInfo;
    int m_CurrentUsercmdID = -1;
    bool m_PerformingMelee = false;

    // Cached models/materials
    model_t* m_ArmsModel = nullptr;
    IMaterial* m_ArmsMaterial = nullptr;
    bool m_CachedArmsModel = false;

    // Weapon state
    bool m_IsMeleeWeaponActive = false;
    bool m_SwitchedWeapons = false;

    // === Constructor ===
    Game();

    // === Interface Retrieval ===
    void* GetInterface(const char* dllname, const char* interfacename);

    // === Logging ===
    static void logMsg(const char* fmt, ...);
    static void errorMsg(const char* msg);

    // === Utility ===
    CBaseEntity* GetClientEntity(int entityIndex);
    char* getNetworkName(uintptr_t* entity);
    void ClientCmd(const char* szCmdString);
    void ClientCmd_Unrestricted(const char* szCmdString);
};

// === Logging Macros (Debug Only) ===
#ifdef _DEBUG
#define LOG(fmt, ...) Game::logMsg("[LOG] " fmt, ##__VA_ARGS__)
#define ERR(msg) Game::errorMsg("[ERROR] " msg)
#else
#define LOG(fmt, ...)
#define ERR(msg)
#endif
