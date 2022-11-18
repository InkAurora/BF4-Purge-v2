#pragma once

#include "Includes.hpp"
#include "Classes.hpp"

Vector3 WorldToScreen(Vector3 entityPos, __int64 pose = -1) {
  SCREEN_X = GetSystemMetrics(SM_CXSCREEN);
  SCREEN_Y = GetSystemMetrics(SM_CYSCREEN);
  matrix3x4_t vProj = getViewProjection();

  entityPos.y += (pose == -1) ? 0 : (pose == 0) ? 1.7f : (pose == 1) ? 1.15f : (pose == 2) ? 0.4f : 0;
  Vector3 result;

  result.z = ((vProj.i.w * entityPos.x) + (vProj.j.w * entityPos.y) + (vProj.k.w * entityPos.z + vProj.l.w));

  if (result.z < 0.000001) return Vector3{};

  result.x = (SCREEN_X / 2) + (SCREEN_X / 2) * ((vProj.i.x * entityPos.x) + (vProj.j.x * entityPos.y) + (vProj.k.x * entityPos.z + vProj.l.x)) / result.z;
  result.y = (SCREEN_Y / 2) - (SCREEN_Y / 2) * ((vProj.i.y * entityPos.x) + (vProj.j.y * entityPos.y) + (vProj.k.y * entityPos.z + vProj.l.y)) / result.z;

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
  Vector3 weaponOffset = getWeaponOffset();
  Vector3 entityBonePos = getEntityBonePosition(index, BONE_INDEX);

  Vector3 ViewCameraPosition = { ViewMI.l.x, ViewMI.l.y - weaponOffset.y, ViewMI.l.z };

  return DistanceVec(ViewCameraPosition, entityBonePos);
}
