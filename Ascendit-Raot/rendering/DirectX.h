#pragma once
#include <dxgi.h>
#include <d3d11.h>

#include "utils.h"
#include "Structures.h"

#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"

class DirectX {

public:
	static bool isWindowFocused();
	static bool getWindowInformation();
	static void hookDirectX();
	static void DisableHooks();

	static HRESULT APIENTRY MJPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static void APIENTRY MJDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	static LRESULT APIENTRY WndProcFunc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	typedef HRESULT(APIENTRY* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	inline static IDXGISwapChainPresent oIDXGISwapChainPresent;

	typedef void(APIENTRY* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	inline static ID3D11DrawIndexed oID3D11DrawIndexed;

	inline static WNDCLASSEX WindowClass;
	inline static HWND WindowHwnd;

	inline static bool ImGui_Initialised = false;
	inline static CursorLockMode lastCursorState = None;

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

private:
	static bool Init();
	static bool InitWindow();
	static bool DeleteWindow();
};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);