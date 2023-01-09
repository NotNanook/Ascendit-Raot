#include "DirectX.h"

bool DirectX::preInit(LPVOID _lpParameter) {
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
			GetWindowText(Hwnd, TempTitle, sizeof(TempTitle));
			Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName(Hwnd, TempClassName, sizeof(TempClassName));
			ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx(Handle, NULL, TempPath, sizeof(TempPath));
			Path = TempPath;

			WindowFocus = true;
			return true;
		}
	}

	lpParameter = _lpParameter;
}

bool DirectX::Init() {
	if (InitWindow() == false) {
		return false;
	}

	HMODULE D3D11Module = GetModuleHandle("d3d11.dll");
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

	DXGI_RATIONAL RefreshRate;
	RefreshRate.Numerator = 60;
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

	MethodsTable = (uint64_t*)::calloc(205, sizeof(uint64_t));
	memcpy(MethodsTable, *(uint64_t**)SwapChain, 18 * sizeof(uint64_t));
	memcpy(MethodsTable + 18, *(uint64_t**)Device, 43 * sizeof(uint64_t));
	memcpy(MethodsTable + 18 + 43, *(uint64_t**)Context, 144 * sizeof(uint64_t));

	MH_Initialize();
	SwapChain->Release();
	SwapChain = NULL;
	Device->Release();
	Device = NULL;
	Context->Release();
	Context = NULL;
	DeleteWindow();
	return true;
}

// maybe unused?
bool DirectX::CheckDirectXVersion() {
	if (GetModuleHandle("d3d11.dll") != NULL) {
		return true;
	}
	return false;
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

bool DirectX::CreateHook(uint16_t Index, void** Original, void* Function) {
	assert(Index >= 0 && Original != NULL && Function != NULL);
	void* target = (void*)MethodsTable[Index];
	if (MH_CreateHook(target, Function, Original) != MH_OK || MH_EnableHook(target) != MH_OK) {
		return false;
	}
	return true;
}

void DirectX::DisableHook(uint16_t Index) {
	assert(Index >= 0);
	MH_DisableHook((void*)MethodsTable[Index]);
}

void DirectX::RemoveAll() {
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	free(MethodsTable);
	MethodsTable = NULL;

	FreeLibraryAndExitThread((HMODULE)lpParameter, TRUE);
}

LRESULT APIENTRY DirectX::WndProcFunc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ShowMenu && ImGui_Initialised) {
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
			drawHelper::setStyle();
			ImGui_Initialised = true;
		}
	}
	// Menu State
	if ((GetAsyncKeyState(VK_RSHIFT) & 1) || (GetAsyncKeyState(VK_ESCAPE) & 1 && ShowMenu)) {
		if (!ShowMenu) {
			drawHelper::lastState = functions.get_lockState();
			functions.set_lockState(None);
		}
		else {
			functions.set_lockState(drawHelper::lastState);
		}
		ShowMenu = !ShowMenu;
	}

	if (GetAsyncKeyState(VK_NUMPAD0) & 1) { 
		RemoveAll(); 
	}

	CheatManager::onUpdate(&DirectX::functions);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = ShowMenu;
	if (ShowMenu == true) {
		drawHelper::drawGui(&functions);
	}
	ImGui::EndFrame();
	ImGui::Render();
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oIDXGISwapChainPresent(pSwapChain, SyncInterval, Flags);
}

void APIENTRY DirectX::MJDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {}