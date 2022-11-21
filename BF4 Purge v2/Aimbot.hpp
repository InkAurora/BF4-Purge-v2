#pragma once

#include "Includes.hpp"
#include "Math.hpp"

vector<entityData> EnemiesList;

void PopulateEnemiesList(int BONE_INDEX) {
  entityData entityStruct;
  EnemiesList.clear();
  for (int i = 0; i <= 70; i++) {
    if (!isEnemy(i)) continue;
    if (isOccluded(i)) continue;

    entityStruct.health = getEntityHealth(i);
    if (entityStruct.health <= 0) continue;

    Vector3 pos = WorldToScreen(getEntityBonePosition(i, BONE_INDEX));
    entityStruct.x = round(pos.x);
    entityStruct.y = round(pos.y);
    if (entityStruct.x == 0 and entityStruct.y == 0) continue;

    entityStruct.index = i;
    entityStruct.distance = DistanceToEntity(i, BONE_INDEX);
    entityStruct.crosshairDistance = DistanceToCrosshair(entityStruct);

    entityStruct.pose = getEntityPose(i);

    EnemiesList.push_back(entityStruct);
  }

  return;
}

int SelectTarget() {
  int AIMBOT_FOV = 20;
  int targetIndex = -1;

  for (entityData entity : EnemiesList) {
    if (entity.crosshairDistance > AIMBOT_FOV) continue;
    
    AIMBOT_FOV = entity.crosshairDistance;
    targetIndex = entity.index;
  }

  return targetIndex;
}

int BONE_INDEX = 0;

void EnableAimbot() {
  while (ENABLE_AIMBOT) {
    PopulateEnemiesList(BONE_INDEX);
    
    int targetIndex = SelectTarget();

    AIMBOT_KEY = VK_RBUTTON;
    
    if (targetIndex == -1) continue;
    if (AIMBOT_KEY == 0) continue;
    
    while (GetAsyncKeyState(AIMBOT_KEY) and ENABLE_AIMBOT) {
      if (isOccluded(targetIndex)) break;
      if (getEntityHealth(targetIndex) <= 0) break;
      Vector3 WorldVector = getWorldVector(targetIndex, BONE_INDEX);
      Vector2 MoveVector = getMoveVector(WorldVector);
      mouse_event(1, MoveVector.x, MoveVector.y, 0, 0);
      Sleep(1000 / 60);
    }
  }

  return;
}
