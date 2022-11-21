#pragma once

#include "Includes.hpp"
#include "Offsets.hpp"

DWORD64 moduleBase;

int SCREEN_X, SCREEN_Y;

bool ENABLE_AIMBOT = true;
DWORD AIMBOT_KEY = 0;

struct entityData {
  int index;
  int x, y;
  int headX, headY;
  float distance;
  float crosshairDistance;
  float health;
  int pose;
  string name;
  bool isEnemy;
  bool isSquadAlly;
};
