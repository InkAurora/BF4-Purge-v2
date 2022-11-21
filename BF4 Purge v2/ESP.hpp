#pragma once

#include "Includes.hpp"
#include "Math.hpp"

vector<entityData> EntityList;


bool show_menu = true;
bool show_ESP = true;
bool show_ESP_allies = true;

ImU32 SQUADALLY_ESP_COLOR = IM_COL32(100, 255, 100, 255);
ImU32 ALLY_ESP_COLOR = IM_COL32(0, 100, 255, 255);
ImU32 ENEMY_ESP_COLOR = IM_COL32(255, 100, 0, 255);

int gmp(entityData entity) {
  return lround((entity.x + entity.headX) / 2);
}

vector<ImVec2> getRectPos(entityData entity) {
  ImVec2 p0, p1;

  int width = 300 * (3.5f / (entity.distance / 1.2f));
  p0 = ImVec2(gmp(entity) - (width / 2), entity.headY - ((entity.y - entity.headY) / 10));
  p1 = ImVec2(gmp(entity) + (width / 2), entity.y + ((entity.y - entity.headY) / 10));

  return { p0, p1 };
}


void PopulateEntities() {
  entityData entityStruct;
  EntityList.clear();
  for (int i = 0; i <= 70; i++) {
    entityStruct.health = getEntityHealth(i);
    if (entityStruct.health <= 0) continue;

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
    entityStruct.name = getEntityName(i);
    //TODO: add distance scalability
    /*entityStruct.scaleX = 3.5f / (entityStruct.distance / 1.1f);
    entityStruct.scaleY = 1;*/

    entityStruct.isEnemy = isEnemy(i);
    entityStruct.isSquadAlly = isSquadAlly(i);

    entityStruct.pose = getEntityPose(i);

    EntityList.push_back(entityStruct);
  }

  return;
}

void DrawBox(ImDrawList* draw_list, entityData entity, ImU32 color) {
  float width = 0.35f;
  Vector3 entPos = getEntityPos(entity.index);
  Vector3 headPos = getEntityBonePosition(entity.index, 104);

  Vector3 b0 = WorldToScreen({ entPos.x + width, entPos.y, entPos.z + width }, -1, true);
  Vector3 b1 = WorldToScreen({ entPos.x + width, entPos.y, entPos.z - width }, -1, true);
  Vector3 b2 = WorldToScreen({ entPos.x - width, entPos.y, entPos.z + width }, -1, true);
  Vector3 b3 = WorldToScreen({ entPos.x - width, entPos.y, entPos.z - width }, -1, true);
  Vector3 t0 = WorldToScreen({ entPos.x + width, headPos.y, entPos.z + width }, -1, true);
  Vector3 t1 = WorldToScreen({ entPos.x + width, headPos.y, entPos.z - width }, -1, true);
  Vector3 t2 = WorldToScreen({ entPos.x - width, headPos.y, entPos.z + width }, -1, true);
  Vector3 t3 = WorldToScreen({ entPos.x - width, headPos.y, entPos.z - width }, -1, true);

  draw_list->AddLine({ b0.x, b0.y }, { b1.x, b1.y }, color);
  draw_list->AddLine({ b0.x, b0.y }, { b2.x, b2.y }, color);
  draw_list->AddLine({ b1.x, b1.y }, { b3.x, b3.y }, color);
  draw_list->AddLine({ b2.x, b2.y }, { b3.x, b3.y }, color);
  draw_list->AddLine({ t0.x, t0.y }, { t1.x, t1.y }, color);
  draw_list->AddLine({ t0.x, t0.y }, { t2.x, t2.y }, color);
  draw_list->AddLine({ t1.x, t1.y }, { t3.x, t3.y }, color);
  draw_list->AddLine({ t2.x, t2.y }, { t3.x, t3.y }, color);
  draw_list->AddLine({ b0.x, b0.y }, { t0.x, t0.y }, color);
  draw_list->AddLine({ b1.x, b1.y }, { t1.x, t1.y }, color);
  draw_list->AddLine({ b2.x, b2.y }, { t2.x, t2.y }, color);
  draw_list->AddLine({ b3.x, b3.y }, { t3.x, t3.y }, color);

  return;
}

void DrawESP(ImDrawList* draw_list) {
  vector<entityData> renderList = EntityList;

  for (entityData entity : renderList) {
    if (!show_ESP_allies and !entity.isEnemy) continue;
    vector<ImVec2> rectPos = getRectPos(entity);
    /*if (!entity.isEnemy) draw_list->AddRect(rectPos[0], rectPos[1], ALLY_ESP_COLOR);
    else if (entity.isSquadAlly) draw_list->AddRect(rectPos[0], rectPos[1], SQUADALLY_ESP_COLOR);
    else if (!isOccluded(entity.index)) draw_list->AddRect(rectPos[0], rectPos[1], ENEMY_ESP_COLOR);
    else draw_list->AddRect(rectPos[0], rectPos[1], 0xFFFFFFFF);*/

    ImU32 ESP_COLOR;
    if (entity.isSquadAlly) ESP_COLOR = SQUADALLY_ESP_COLOR;
    else if (!entity.isEnemy) ESP_COLOR = ALLY_ESP_COLOR;
    else if (!isOccluded(entity.index)) ESP_COLOR = ENEMY_ESP_COLOR;
    else ESP_COLOR = 0xFFFF30F0;

    DrawBox(draw_list, entity, ESP_COLOR);

    string distanceStr = to_string(lround(entity.distance)) + "m";
    draw_list->AddText(ImVec2(gmp(entity), rectPos[1].y + 5), 0xFFFFFFFF, distanceStr.c_str());

    string healthStr = "HP " + to_string(lround(entity.health));
    draw_list->AddText(ImVec2(rectPos[0].x, rectPos[0].y - 15), 0xFFFFFFFF, healthStr.c_str());
  }

  return;
}
