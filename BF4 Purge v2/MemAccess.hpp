#pragma once

#include "Includes.hpp"

bool isValidPtr(void* pointer) {
  DWORD64 ptr = (DWORD64)pointer;
  return (ptr >= 0x10000 && ptr <= 0x0F000000000000);
}

void readBytes(DWORD64 address, void* destination, SIZE_T size) {
  memcpy(destination, (void*)address, size);
}

void writeBytes(DWORD64 address, void* bytes, SIZE_T size, int debug = 0) {
  DWORD protect;
  VirtualProtect((LPVOID)address, size, PAGE_EXECUTE_READWRITE, &protect);
  memcpy((void*)address, &bytes, size);
  VirtualProtect((LPVOID)address, size, protect, &protect);
}

string ReadString(DWORD64 address, size_t size) {
  LPCVOID param = (LPCVOID)address;

  char* str = new char[size];
  readBytes(address, str, size);

  string temp(&str[0], &str[size]);
  char* t_str = strtok(&temp[0], "\0");
  if (t_str != nullptr) return t_str;
  return string("");
}

vector<float> ReadVector(DWORD64 vectorAddress) {
  vector<float> vector3;

  float temp;
  for (int i = 0; i < 3; i++) {
	readBytes(vectorAddress + (i * 0x4), &temp, 4);
	vector3.push_back(temp);
  }

  return vector3;
}

vector<vector<float>> ReadMatrix(DWORD64 mAddress) {
  vector<vector<float>> matrix(4, vector<float>(4));

  __int64 offset = 0;
  float temp;
  for (__int64 i = 0; i < 4; i++) {
	for (__int64 j = 0; j < 4; j++) {
	  readBytes(mAddress + offset, &temp, 4);
	  matrix.at(i).at(j) = temp;
	  offset += 0x4;
	}
  }

  return matrix;
}
