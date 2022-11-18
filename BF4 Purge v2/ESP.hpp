#pragma once

#include "Includes.hpp"
#include "Math.hpp"

struct entityESP {
  int index;
  int x, y;
  int headX, headY;
  float distance;
  float scaleX, scaleY;
  float health;
  string name;
  bool isEnemy;
  bool isSquadAlly;
};

vector<entityESP> DrawList;

void PopulateESP() {
  entityESP entityStruct;
  DrawList.clear();
  for (int i = 0; i <= 70; i++) {
    if (getEntityHealth(i) == 0.0) continue;

    Vector3 pos = WorldToScreen(getEntityPos(i));
    entityStruct.x = round(pos.x);
    entityStruct.y = round(pos.y);
    if (entityStruct.x == 0 and entityStruct.y == 0) continue;

    Vector3 headPos = WorldToScreen(getEntityBonePosition(i, 104));
    entityStruct.headX = headPos.x;
    entityStruct.headY = headPos.y;
    if (entityStruct.headX == 0 and entityStruct.headY == 0) continue;

    entityStruct.index = i;
    entityStruct.distance = DistanceToEntity(i);
    entityStruct.health = getEntityHealth(i);
    entityStruct.name = getEntityName(i);
    //TODO: add distance scalability
    entityStruct.scaleX = 3.5f / entityStruct.distance;
    entityStruct.scaleY = 1;

    entityStruct.isEnemy = isEnemy(i);
    entityStruct.isSquadAlly = isSquadAlly(i);

    DrawList.push_back(entityStruct);
  }

  return;
}
