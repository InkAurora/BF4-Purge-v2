#pragma once

#include "Includes.hpp"
#include "ESP.hpp"

typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);
present p_present;
present p_present_target;

bool get_present_pointer() {
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 2;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = GetForegroundWindow();
  sd.SampleDesc.Count = 1;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  IDXGISwapChain* swap_chain;
  ID3D11Device* device;

  const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
  if (D3D11CreateDeviceAndSwapChain(
	NULL,
	D3D_DRIVER_TYPE_HARDWARE,
	NULL,
	0,
	feature_levels,
	2,
	D3D11_SDK_VERSION,
	&sd,
	&swap_chain,
	&device,
	nullptr,
	nullptr) == S_OK)
  {
	void** p_vtable = *reinterpret_cast<void***>(swap_chain);
	swap_chain->Release();
	device->Release();
	//context->Release();
	p_present_target = (present)p_vtable[8];
	return true;
  }
  return false;
}

WNDPROC oWndProc;
// Win32 message handler your application need to call.
// - You should COPY the line below into your .cpp code to forward declare the function and then you can call it.
// - Call from your application's message handler. Keep calling your message handler unless this function returns TRUE.
// Forward declare message handler from imgui_impl_win32.cpp
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  // handle input issues here.

  if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;

  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool show_menu = true;
bool show_ESP = false;
bool show_ESP_allies = true;

string testText = "";

bool init = false;
HWND window = NULL;
ID3D11Device* p_device = NULL;
ID3D11DeviceContext* p_context = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;

vector<entityESP> renderList;

ImU32 SQUADALLY_ESP_COLOR = IM_COL32(100, 255, 100, 255);
ImU32 ALLY_ESP_COLOR = IM_COL32(0, 100, 255, 255);
ImU32 ENEMY_ESP_COLOR = IM_COL32(255, 100, 0, 255);

int gmp(entityESP entity) {
  return lround((entity.x + entity.headX) / 2);
}

vector<ImVec2> getRectPos(entityESP entity) {
  int width = 300;
  
  ImVec2 p0, p1;

  width = width * entity.scaleX;
  p0 = ImVec2(gmp(entity) - (width / 2), entity.headY - ((entity.y - entity.headY) / 10));
  p1 = ImVec2(gmp(entity) + (width / 2), entity.y + ((entity.y - entity.headY) / 10));

  return { p0, p1 };
}

static long __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags) {
  if (!init) {
	if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&p_device))) {
	  p_device->GetImmediateContext(&p_context);

	  DXGI_SWAP_CHAIN_DESC sd;
	  p_swap_chain->GetDesc(&sd);
	  window = sd.OutputWindow;

	  ID3D11Texture2D* pBackBuffer;
	  p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	  p_device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
	  pBackBuffer->Release();
	  oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

	  ImGui::CreateContext();
	  ImGuiIO& io = ImGui::GetIO();
	  ImGui_ImplWin32_Init(window);
	  ImGui_ImplDX11_Init(p_device, p_context);
	  init = true;
	}
	else
	  return p_present(p_swap_chain, sync_interval, flags);
  }

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();

  if (show_menu) {
	ImGui::Begin("BF4 Purge v2", &show_menu);
	ImGui::SetWindowSize(ImVec2(200, 500), ImGuiCond_Always);
	ImGui::Text("Options:");
	ImGui::Checkbox("Enable ESP", &show_ESP);
	ImGui::Checkbox("ESP Allies", &show_ESP_allies);
	ImGui::Text(testText.c_str());
	ImGui::End();
  }

  if (show_ESP) {
	ImGuiIO& io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::Begin("XXX", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	PopulateESP();

	renderList = DrawList;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImDrawList* draw_list = window->DrawList;

	for (entityESP entity : renderList) {
	  if (!show_ESP_allies and !entity.isEnemy) continue;
	  vector<ImVec2> rectPos = getRectPos(entity);
	  if (entity.isEnemy) draw_list->AddRect(rectPos[0], rectPos[1], ENEMY_ESP_COLOR);
	  else if (entity.isSquadAlly) draw_list->AddRect(rectPos[0], rectPos[1], SQUADALLY_ESP_COLOR);
	  else draw_list->AddRect(rectPos[0], rectPos[1], ALLY_ESP_COLOR);

	  string distanceStr = to_string(lround(entity.distance)) + "m";
	  draw_list->AddText(ImVec2(gmp(entity), rectPos[1].y + 5), 0xFFFFFFFF, distanceStr.c_str());

	  string healthStr = "HP " + to_string(lround(entity.health));
	  draw_list->AddText(ImVec2(gmp(entity), rectPos[0].y - 15), 0xFFFFFFFF, healthStr.c_str());
	}

	window->DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
  }

  ImGui::EndFrame();

  ImGui::Render();

  p_context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

  return p_present(p_swap_chain, sync_interval, flags);
}

bool InitializeVisuals() {
  Sleep(50);
  if (!get_present_pointer()) {
	return false;
  }

  if (MH_Initialize() != MH_OK) {
	return false;
  }

  if (MH_CreateHook(reinterpret_cast<void**>(p_present_target), &detour_present, reinterpret_cast<void**>(&p_present)) != MH_OK) {
	return false;
  }

  if (MH_EnableHook(p_present_target) != MH_OK) {
	return false;
  }

  return true;
}

bool ShutdownVisuals() {
  if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK) {
	return false;
  }
  if (MH_Uninitialize() != MH_OK) {
	return false;
  }

  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();

  if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }
  if (p_context) { p_context->Release(); p_context = NULL; }
  if (p_device) { p_device->Release(); p_device = NULL; }
  SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc)); // "unhook"

  return true;
}
