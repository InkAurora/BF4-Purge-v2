#pragma once

#include "Includes.hpp"
#include "Classes.hpp"

const float  PI_F = 3.1415f;

float RadToDeg(float rad) {
  return (rad * (180 / PI_F));
}

float DegToRad(float deg) {
  return (deg * (PI_F / 180));
}

float PixToDeg(int pix) {
  return (RadToDeg(getFovY()) / SCREEN_Y) * pix;
}

float DegToPix(float deg) {
  return (SCREEN_Y / RadToDeg(getFovY())) * deg;
}

Vector3 WorldToScreen(Vector3 entityPos, int pose = -1, bool overrideScreenBorder = false) {
  SCREEN_X = GetSystemMetrics(SM_CXSCREEN);
  SCREEN_Y = GetSystemMetrics(SM_CYSCREEN);
  matrix3x4_t vProj = getViewProjection();

  entityPos.y += (pose == -1) ? 0 : (pose == 0) ? 1.7f : (pose == 1) ? 1.15f : (pose == 2) ? 0.4f : 0;
  Vector3 result;

  result.z = ((vProj.i.w * entityPos.x) + (vProj.j.w * entityPos.y) + (vProj.k.w * entityPos.z + vProj.l.w));

  if (result.z < 0.000001) return Vector3{};

  result.x = (SCREEN_X / 2) + (SCREEN_X / 2) * ((vProj.i.x * entityPos.x) + (vProj.j.x * entityPos.y) + (vProj.k.x * entityPos.z + vProj.l.x)) / result.z;
  result.y = (SCREEN_Y / 2) - (SCREEN_Y / 2) * ((vProj.i.y * entityPos.x) + (vProj.j.y * entityPos.y) + (vProj.k.y * entityPos.z + vProj.l.y)) / result.z;

  if (overrideScreenBorder) return result;
  if (result.x > 0 and result.x < SCREEN_X and result.y > 0 && result.y < SCREEN_Y) return result;
  return Vector3{};
}

float DistanceVec(Vector3 v1, Vector3 v2) {
  Vector3 fV;

  fV = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
 
  return sqrt(fV.x * fV.x + fV.y * fV.y + fV.z * fV.z);
}

float DistanceToEntity(int index, int BONE_INDEX = 104) {
  matrix3x4_t ViewMI = getViewMatrixInverse();
  Vector3 WeaponOffset = getWeaponOffset();
  Vector3 EntityBonePos = getEntityBonePosition(index, BONE_INDEX);

  Vector3 ViewCameraPosition = { ViewMI.l.x, ViewMI.l.y - WeaponOffset.y, ViewMI.l.z };

  return DistanceVec(ViewCameraPosition, EntityBonePos);
}

float DistanceToCrosshair(entityData entity) {
  int mpX, mpY;

  mpX = SCREEN_X / 2;
  mpY = SCREEN_Y / 2;

  Vector2 distVec = { abs(mpX - entity.x), abs(mpY - entity.y) };

  return PixToDeg(sqrt(distVec.x * distVec.x + distVec.y * distVec.y));
}

Vector3 getWorldVector(int index, int BONE_INDEX) {
  matrix3x4_t ViewMI = getViewMatrixInverse();
  Vector3 WeaponOffset = getWeaponOffset();
  Vector3 WeaponVelocity = getWeaponVel();
  Vector2 WeaponZeroing = getWeaponZeroing();
  float WeaponGravity = getWeaponGravity();
  Vector3 EntityBonePos = getEntityBonePosition(index, BONE_INDEX);
  Vector3 EntityVel = getEntityVel(index);
  Vector3 LocalPlayerVel = getEntityVel(0, true);

  Vector3 ViewCameraPosition = { ViewMI.l.x, ViewMI.l.y - WeaponOffset.y, ViewMI.l.z };

  float DistanceToEnemy = DistanceVec(ViewCameraPosition, EntityBonePos);
  float Time = DistanceToEnemy / WeaponVelocity.z;

  Vector3 AimVector = { 
    EntityBonePos.x + (EntityVel.x * Time) - (LocalPlayerVel.x * Time),
    EntityBonePos.y + (EntityVel.y * Time) - (LocalPlayerVel.y * Time),
    EntityBonePos.z + (EntityVel.z * Time) - (LocalPlayerVel.z * Time) 
  };
  Vector3 WorldVector = WorldToScreen(AimVector);

  float BulletDrop = 0.5f * WeaponGravity * Time * Time;
  float PitchCompensation = atan2(BulletDrop, DistanceToEnemy);
  PitchCompensation += atan2(WeaponVelocity.y, WeaponVelocity.z);

  WorldVector.y += DegToPix(RadToDeg(PitchCompensation));
  WorldVector.y += DegToPix(WeaponZeroing.y);

  return WorldVector;
}

Vector2 getMoveVector(Vector3 WorldVector) {
  Vector2 Move = { 0 , 0 };
  Vector2 mid = { SCREEN_X / 2, SCREEN_Y / 2 };

  if (WorldVector.x == 0 or WorldVector.y == 0) return Move;

  Move.x = WorldVector.x - mid.x;
  Move.y = WorldVector.y - mid.y;

  return Move;
}
