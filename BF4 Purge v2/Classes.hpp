#pragma once

#include "Includes.hpp"
#include "Globals.hpp"
#include "MemAccess.hpp"

struct Vector3 {
  float x;
  float y;
  float z;
};

struct Vector4 {
  float x, y, z, w;
};

struct matrix3x4_t {
  Vector4 i, j, k, l;
};

class ClientGameContext;
class PlayerManager;
class LocalPlayer;
class Soldier;
class ClientSoldier;
class VehicleEntity;
class Position;
class Weapon;
class WeaponData;
class FiringFunction;
class BulletEntity;
class GunSway;
class PlayerArray;
class Player;
class Vehicle;
class WeaponModifier;
class Silencer;
class WeaponZeroing;
class Modes;
class Ragdoll;
class BoneData;

class ClientGameContext
{
public:
  char pad_0x0000[0x60]; //0x0000
  PlayerManager* pPlayerManager; //0x0060 
  char pad_0x0068[0x28]; //0x0068
  float PlayerFOV; //0x0090 

}; //Size=0x0094

class PlayerManager
{
public:
  char pad_0x0000[0x540]; //0x0000
  LocalPlayer* pLocalPlayer; //0x0540
  PlayerArray* pPlayerArray; //0x0548

}; //Size=0x0550

class LocalPlayer
{
public:
  char pad_0x0000[0x13CC]; //0x0000
  __int32 TeamId; //0x13CC 
  char pad_0x13D0[0xF0]; //0x13D0
  VehicleEntity* pVehicleEntity; //0x14C0 
  char pad_0x14C8[0x8]; //0x14C8
  Soldier* pSoldier; //0x14D0 
  char pad_0x14D8[0x100]; //0x14D8
  __int32 SquadId; //0x15D8 
  unsigned char IsSquadLeader; //0x15DC 
  unsigned char IsPrivateSquad; //0x15DD 
  char pad_0x15DE[0x258]; //0x15DE
  char LocalPlayerName[16]; //0x89EFE9C0 

}; //Size=0x1846

class Soldier
{
public:
  char pad_0x0000[0x140]; //0x0000
  ClientSoldier* pClientSoldier; //0x0140 
  char pad_0x0148[0x348]; //0x0148
  Position* pPosition; //0x0490 
  char pad_0x0498[0x40]; //0x0498
  float Yaw; //0x04D8 
  float Pitch; //0x04DC 
  char pad_0x04E0[0x10]; //0x04E0
  __int32 PoseType; //0x04F0
  unsigned char SoldierChams; //0x04F4 
  char pad_0x04F5[0x88]; //0x04F5
  Ragdoll* pRagdoll; //0x0580 
  char pad_0x0588[0x25]; //0x0588
  unsigned char IsSprinting; //0x05B0 
  unsigned char IsOccluded; //0x05B1 

}; //Size=0x04F5

class ClientSoldier
{
public:
  char pad_0x0000[0x20]; //0x0000
  float Health; //0x0020 

}; //Size=0x0024

class VehicleEntity
{
public:
  char pad_0x0000[0x4D0]; //0x0000
  unsigned char VehicleChams; //0x04D3 

}; //Size=0x04D4

class Position
{
public:
  char pad_0x0000[0x30]; //0x0000
  Vector3 Coords; //0x0030 
  char pad_0x003C[0x14]; //0x003C
  Vector3 Velocity; //0x0050 

}; //Size=0x005C

class Weapon
{
public:
  char pad_0x0000[0x128]; //0x0000
  WeaponData* pWeaponData; //0x0128 

}; //Size=0x0130

class WeaponData
{
public:
  char pad_0x0000[0x10]; //0x0000
  FiringFunction* pFiringFunction; //0x0010 
  char pad_0x0018[0x18]; //0x0018
  GunSway* pGunSway; //0x0030 

}; //Size=0x0038

class FiringFunction
{
public:
  char pad_0x0000[0x60]; //0x0000
  Vector3 Offset; //0x0060
  char pad_0x006C[0x14]; //0x006C
  Vector3 Velocity; //0x0080
  char pad_0x008C[0x24]; //0x008C
  BulletEntity* pBulletEntity; //0x00B0
  char pad_0x00B8[0x20]; //0x00B8
  __int32 BulletsPerShell; //0x00D8 
  __int32 BulletsPerShot; //0x00DC 
  __int32 BulletsPerBurst; //0x00E0 
  char pad_0x00E4[0xE4]; //0x00E4
  float RateOfFire; //0x01C8 
  float RateOfFireForBurst; //0x01CC 

}; //Size=0x01D0

class BulletEntity
{
public:
  char pad_0x0000[0x90]; //0x0000
  float InitialSpeed; //0x0090 
  float TimeToLive; //0x0094 
  char pad_0x0098[0x98]; //0x0098
  float Gravity; //0x0130 
  float ImpactImpulse; //0x0134 
  char pad_0x0138[0x1C]; //0x0138
  float StartDamage; //0x0154 
  float EndDamage; //0x0158 
  float DamageFalloffStartDistance; //0x015C 
  float DamageFalloffEndDistance; //0x0160 
  char pad_0x0164[0x8]; //0x0164
  unsigned char InstantHit; //0x016D 

}; //Size=0x016E

class GunSway
{
public:
  char pad_0x0000[0x430]; //0x0000
  float RecoilSight; //0x0430 
  float SpreadSight; //0x0434 
  float RecoilHip; //0x0438 
  float SpreadHip; //0x043C 

}; //Size=0x0440

class PlayerArray
{
public:
  Player* pPlayer; //0x0000

}; //Size=0x0008

class Player
{
public:
  char pad_0x0000[0x18]; //0x0000
  Vehicle* pVehicle; //0x0018 
  char pad_0x0020[0x13AC]; //0x0020
  __int32 TeamId; //0x13CC 
  char pad_0x13D0[0xF0]; //0x13D0
  VehicleEntity* pVehicleEntity; //0x14C0 
  char pad_0x14C8[0x8]; //0x14C8
  Soldier* pSoldier; //0x14D0 
  char pad_0x14D8[0x100]; //0x14D8
  __int32 SquadId; //0x15D8 
  unsigned char IsSquadLeader; //0x15DC 
  unsigned char IsPrivateSquad; //0x15DD 
  char pad_0x15DE[0x256]; //0x15DE
  char PlayerName[16]; //0x89EFE9C0 

}; //Size=0x1846

class Ragdoll
{
public:
  char pad_0x0000[0xB0]; //0x0000
  BoneData* pBoneData; //0x00B0 

}; //Size=0x00B8

class BoneData
{
public:

}; //Size=0x0000

class Vehicle
{
public:
  char VehicleName[16]; //0x89EFE9C0

}; //Size=0x0010

class WeaponModifier
{
public:
  char pad_0x0000[0x68]; //0x0000
  Silencer* pSilencer; //0x0068 
  char pad_0x0070[0x50]; //0x0070
  WeaponZeroing* pWeaponZeroing; //0x00C0 

}; //Size=0x00C8

class Silencer
{
public:
  char pad_0x0000[0x20]; //0x0000
  Vector3 Velocity; //0x0020 

}; //Size=0x002C

class WeaponZeroing
{
public:
  char pad_0x0000[0x18]; //0x0000
  Modes* pModes; //0x0018 

}; //Size=0x0020

class Modes
{
public:
  Vector3 Zeroing; //0x0000 

}; //Size=0x000C



ClientGameContext* cClientGameContext;
Weapon* cWeapon;

Player* getEntityPtr(int index) {
  if (isValidPtr(cClientGameContext)) {
    if (isValidPtr(cClientGameContext->pPlayerManager)) {
      PlayerArray* pPlayerArr = (PlayerArray*)cClientGameContext->pPlayerManager->pPlayerArray;
      pPlayerArr += index;
      if (isValidPtr(pPlayerArr))
        if (isValidPtr(pPlayerArr->pPlayer)) {
          return pPlayerArr->pPlayer;
        }
    }
  }

  return nullptr;
}

Player* getLocalPlayerPtr() {
  if (isValidPtr(cClientGameContext)) {
    if (isValidPtr(cClientGameContext->pPlayerManager)) {
      PlayerArray* pLocalP = (PlayerArray*)cClientGameContext->pPlayerManager->pLocalPlayer;
      if (isValidPtr(pLocalP))
        if (isValidPtr(pLocalP->pPlayer)) {
          return pLocalP->pPlayer;
        }
    }
  }

  return nullptr;
}

Vector3 getEntityPos(int index) {
  Player* pPlayer = getEntityPtr(index);
  if (isValidPtr(pPlayer)) {
    if (isValidPtr(pPlayer->pSoldier)) {
      if (isValidPtr(pPlayer->pSoldier->pPosition)) {
        return pPlayer->pSoldier->pPosition->Coords;
      }
    }
  }

  return Vector3{ 0, 0, 0 };
}

Vector3 getEntityVel(int index) {
  Player* pPlayer = getEntityPtr(index);
  if (isValidPtr(pPlayer)) {
    if (isValidPtr(pPlayer->pSoldier)) {
      if (isValidPtr(pPlayer->pSoldier->pPosition)) {
        return pPlayer->pSoldier->pPosition->Velocity;
      }
    }
  }

  return Vector3{ 0, 0, 0 };
}

float getEntityHealth(int index) {
  Player* pPlayer = getEntityPtr(index);
  if (isValidPtr(pPlayer)) {
    if (isValidPtr(pPlayer->pSoldier)) {
      if (isValidPtr(pPlayer->pSoldier->pClientSoldier)) {
        return pPlayer->pSoldier->pClientSoldier->Health;
      }
    }
  }

  return 0.0;
}

string getEntityName(int index) {
  Player* pPlayer = getEntityPtr(index);
  if (isValidPtr(pPlayer)) return pPlayer->PlayerName;

  return "";
}

bool isEnemy(int index) {
  Player* pLocalPlayer = getLocalPlayerPtr();
  Player* pPlayer = getEntityPtr(index);
  if (isValidPtr(pLocalPlayer) and isValidPtr(pPlayer)) {
    if (pLocalPlayer->TeamId == pPlayer->TeamId) return false;
    return true;
  }

  return false;
}

bool isSquadAlly(int index) {
  Player* pLocalPlayer = getLocalPlayerPtr();
  Player* pPlayer = getEntityPtr(index);
  if (isValidPtr(pLocalPlayer) and isValidPtr(pPlayer)) {
    if (pLocalPlayer->TeamId == pPlayer->TeamId) {
      if (pLocalPlayer->SquadId == pPlayer->SquadId) return true;
    }
    return false;
  }

  return false;
}

WeaponData* getWeaponData() {
  if (isValidPtr(cWeapon)) {
    if (isValidPtr(cWeapon->pWeaponData)) {
      return cWeapon->pWeaponData;
    }
  }

  return nullptr;
}

Vector3 getWeaponOffset() {
  if (isValidPtr(cWeapon)) {
    if (isValidPtr(cWeapon->pWeaponData)) {
      if (isValidPtr(cWeapon->pWeaponData->pFiringFunction)) {
        return cWeapon->pWeaponData->pFiringFunction->Offset;
      }
    }
  }

  return Vector3{};
}

Vector3 getEntityBonePosition(int index, int bone_index) {
  Player* pPlayer = getEntityPtr(index);
  if (isValidPtr(pPlayer)) {
    if (isValidPtr(pPlayer->pSoldier)) {
      if (isValidPtr(pPlayer->pSoldier->pRagdoll)) {
        if (isValidPtr(pPlayer->pSoldier->pRagdoll->pBoneData)) {
          Vector3 bonePos = (Vector3)*(Vector3*)(pPlayer->pSoldier->pRagdoll->pBoneData + (bone_index * 0x20));
          return bonePos;
        }
      }
    }
  }

  return Vector3{};
}


class GameRenderer;
class RenderView;

class GameRenderer
{
public:
  char pad_0x0000[0x60]; //0x0000
  RenderView* pRenderView; //0x0060 

}; //Size=0x0068

class RenderView
{
public:
  char pad_0x0000[0xB4]; //0x0000
  float ClientFovY; //0x00B4 
  char pad_0x00B8[0x198]; //0x00B8
  float ClientFovX; //0x0250 
  char pad_0x0254[0x8C]; //0x0254
  matrix3x4_t ViewMatrixInverse; //0x02E0 
  char pad_0x0320[0x100]; //0x0320
  matrix3x4_t ViewProjection; //0x0420 

}; //Size=0x0460

GameRenderer* cGameRenderer;

matrix3x4_t getViewMatrixInverse() {
  if (isValidPtr(cGameRenderer)) {
    if (isValidPtr(cGameRenderer->pRenderView)) {
      return cGameRenderer->pRenderView->ViewMatrixInverse;
    }
  }

  return matrix3x4_t{};
}

matrix3x4_t getViewProjection() {
  if (isValidPtr(cGameRenderer)) {
    if (isValidPtr(cGameRenderer->pRenderView)) {
      return cGameRenderer->pRenderView->ViewProjection;
    }
  }

  return matrix3x4_t{};
}

float getFovY() {
  if (isValidPtr(cGameRenderer)) {
    if (isValidPtr(cGameRenderer->pRenderView)) {
      return cGameRenderer->pRenderView->ClientFovY;
    }
  }

  return 0.0;
}
