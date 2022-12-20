#pragma once
#include <cassert>
#include <dxgi.h>
#include <d3d11.h>
#include "Functions.h"
#include "drawHelper.h"
#include <../Directories/MinHook/Include/MinHook.h>
#include <../Directories/ImGui/imgui_impl_dx11.h>
#include <Directories/ImGui/imgui_impl_win32.h>
#include <../Directories/ImGui/imgui.h>

class DirectX {

public:
	static bool preInit();
	static bool Init();
	static bool CheckDirectXVersion();
	static bool InitWindow();
	static bool DeleteWindow();
	static bool CreateHook(uint16_t Index, void** Original, void* Function);
	static void DisableHook(uint16_t Index);
	static void RemoveAll();

	static HRESULT APIENTRY MJPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static void APIENTRY MJDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	static LRESULT APIENTRY WndProcFunc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	typedef HRESULT(APIENTRY* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	inline static IDXGISwapChainPresent oIDXGISwapChainPresent;

	typedef void(APIENTRY* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	inline static ID3D11DrawIndexed oID3D11DrawIndexed;

	inline static WNDCLASSEX WindowClass;
	inline static HWND WindowHwnd;
	inline static uint64_t* MethodsTable = NULL;
	inline static int D3D11 = 3;

	inline static bool ShowMenu = false;
	inline static bool ImGui_Initialised = false;

	inline static Functions functions = Functions(GetModuleHandle(NULL));

	inline static DWORD ID;
	inline static HANDLE Handle;
	inline static HWND Hwnd;
	inline static HMODULE Module;
	inline static WNDPROC WndProc;
	inline static int WindowWidth;
	inline static int WindowHeight;
	inline static LPCSTR Title;
	inline static LPCSTR ClassName;
	inline static LPCSTR Path;

	inline static ID3D11Device* Device;
	inline static ID3D11DeviceContext* DeviceContext;
	inline static ID3D11RenderTargetView* RenderTargetView;
};

// Things that cant be static because idk

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);