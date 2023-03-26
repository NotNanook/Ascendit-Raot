#include "CheatManager.h"
#include "DirectX.h"
#include "Gui.h"
#include "Functions.h"
#include <Psapi.h>

bool DirectX::isWindowFocused() {
	DWORD ForegroundWindowProcessID;
	GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
	return GetCurrentProcessId() == ForegroundWindowProcessID;
}

bool DirectX::getWindowInformation() {
	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetCurrentProcessId() == ForegroundWindowProcessID) {

			ID = GetCurrentProcessId();
			Handle = GetCurrentProcess();
			Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Hwnd, &TempRect);
			WindowWidth = TempRect.right - TempRect.left;
			WindowHeight = TempRect.bottom - TempRect.top;

			char TempTitle[MAX_PATH];
			GetWindowTextA(Hwnd, TempTitle, sizeof(TempTitle));
			Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassNameA(Hwnd, TempClassName, sizeof(TempClassName));
			ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameExA(Handle, NULL, TempPath, sizeof(TempPath));
			Path = TempPath;

			WindowFocus = true;
			return true;
		}
	}

	return false;
}

void DirectX::hookDirectX() {
	bool InitHook = false;
	while (!InitHook) {
		if (Init()) {
			utils::CreateHook(8, (void**)&oIDXGISwapChainPresent, MJPresent);
			utils::CreateHook(12, (void**)&oID3D11DrawIndexed, MJDrawIndexed);
			InitHook = true;
		}
	}
	return;
}

bool DirectX::Init() {
	if (InitWindow() == false) {
		return false;
	}

	HMODULE D3D11Module = GetModuleHandleA("d3d11.dll");
	if (D3D11Module == NULL) {
		DeleteWindow();
		return false;
	}

	void* D3D11CreateDeviceAndSwapChain = GetProcAddress(D3D11Module, "D3D11CreateDeviceAndSwapChain");
	if (D3D11CreateDeviceAndSwapChain == NULL) {
		DeleteWindow();
		return false;
	}

	D3D_FEATURE_LEVEL FeatureLevel;
	const D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

	DEVMODE devMode;
	int refreshRate = 60;
	devMode.dmSize = sizeof(DEVMODE);
	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode))
	{
		refreshRate = devMode.dmDisplayFrequency;
	}

	DXGI_RATIONAL RefreshRate;
	RefreshRate.Numerator = refreshRate;
	RefreshRate.Denominator = 1;

	DXGI_MODE_DESC BufferDesc;
	BufferDesc.Width = 100;
	BufferDesc.Height = 100;
	BufferDesc.RefreshRate = RefreshRate;
	BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SAMPLE_DESC SampleDesc;
	SampleDesc.Count = 1;
	SampleDesc.Quality = 0;

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChainDesc.BufferDesc = BufferDesc;
	SwapChainDesc.SampleDesc = SampleDesc;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = WindowHwnd;
	SwapChainDesc.Windowed = 1;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGISwapChain* SwapChain;
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;

	if (((long(__stdcall*)(
		IDXGIAdapter*,
		D3D_DRIVER_TYPE,
		HMODULE,
		UINT,
		const D3D_FEATURE_LEVEL*,
		UINT,
		UINT,
		const DXGI_SWAP_CHAIN_DESC*,
		IDXGISwapChain**,
		ID3D11Device**,
		D3D_FEATURE_LEVEL*,
		ID3D11DeviceContext**))(D3D11CreateDeviceAndSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, FeatureLevels, 1, D3D11_SDK_VERSION, &SwapChainDesc, &SwapChain, &Device, &FeatureLevel, &Context) < 0)
	{
		DeleteWindow();
		return false;
	}

	utils::MethodsTable = (uint64_t*)::calloc(205, sizeof(uint64_t));

	memcpy(utils::MethodsTable, *(uint64_t**)SwapChain, 18 * sizeof(uint64_t));
	memcpy(utils::MethodsTable + 18, *(uint64_t**)Device, 43 * sizeof(uint64_t));
	memcpy(utils::MethodsTable + 18 + 43, *(uint64_t**)Context, 144 * sizeof(uint64_t));

	SwapChain->Release();
	SwapChain = NULL;
	Device->Release();
	Device = NULL;
	Context->Release();
	Context = NULL;
	DeleteWindow();
	return true;
}

bool DirectX::InitWindow() {
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = DefWindowProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = GetModuleHandle(NULL);
	WindowClass.hIcon = NULL;
	WindowClass.hCursor = NULL;
	WindowClass.hbrBackground = NULL;
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = "MJ";
	WindowClass.hIconSm = NULL;
	RegisterClassEx(&WindowClass);
	WindowHwnd = CreateWindow(WindowClass.lpszClassName, "DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, WindowClass.hInstance, NULL);
	if (WindowHwnd == NULL) {
		return false;
	}
	return true;
}

bool DirectX::DeleteWindow() {
	DestroyWindow(WindowHwnd);
	UnregisterClass(WindowClass.lpszClassName, WindowClass.hInstance);
	if (WindowHwnd != NULL) {
		return false;
	}
	return true;
}

LRESULT APIENTRY DirectX::WndProcFunc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (Gui::isEnabled && ImGui_Initialised) {
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
		return true;
	}
	return CallWindowProc(WndProc, hwnd, uMsg, wParam, lParam);
}

HRESULT APIENTRY DirectX::MJPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!ImGui_Initialised) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&Device))) {
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

			Device->GetImmediateContext(&DeviceContext);

			DXGI_SWAP_CHAIN_DESC Desc;
			pSwapChain->GetDesc(&Desc);
			WindowHwnd = Desc.OutputWindow;

			ID3D11Texture2D* BackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
			Device->CreateRenderTargetView(BackBuffer, NULL, &RenderTargetView);
			BackBuffer->Release();

			ImGui_ImplWin32_Init(WindowHwnd);
			ImGui_ImplDX11_Init(Device, DeviceContext);
			ImGui_ImplDX11_CreateDeviceObjects();
			ImGui::GetIO().ImeWindowHandle = Hwnd;
			WndProc = (WNDPROC)SetWindowLongPtr(Hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProcFunc);
			Gui::setStyle();
			ImGui_Initialised = true;
		}
	}
	
	CheatManager::checkUserInput();

	if ((GetAsyncKeyState(VK_RSHIFT) & 1) || (GetAsyncKeyState(VK_ESCAPE) & 1 && Gui::isEnabled)) {
		if (!Gui::isEnabled) {
			lastCursorState = Functions::getLockState();
			Functions::setLockState(None);
		}
		else {
			Functions::setLockState(lastCursorState);
		}
		Gui::isEnabled = !Gui::isEnabled;
	}

	if (GetAsyncKeyState(VK_NUMPAD0) & 1) { 
		utils::RemoveAllHooks();
		return oIDXGISwapChainPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = Gui::isEnabled;
	if (Gui::isEnabled == true) Gui::drawGui();
	CheatManager::onRenderUpdate();
	ImGui::EndFrame();
	ImGui::Render();
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oIDXGISwapChainPresent(pSwapChain, SyncInterval, Flags);
}

void APIENTRY DirectX::MJDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {}