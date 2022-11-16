#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <future>
#include <string>

#include "MinHook.h"
#if _WIN64
#pragma comment (lib, "libMinHook.x64.lib")
#else
#pragma comment (lib, "libMinHook.x86.lib")
#endif

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

using namespace std;
