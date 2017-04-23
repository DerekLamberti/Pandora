// WorldBuilder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ImGuiWrapperD3D11.h"
#include "InputTracker.h"

#include <Base/Base.h> 
#include <Base/Memory.h>

#include <SDL.h>
#include <d3d11.h>


using namespace Pandora;

const int32 Width = 640;
const int32 Height = 480;


class D3D11RenderBackend
{
public:
	D3D11RenderBackend()
		: m_Device(nullptr)
		, m_DeviceContext(nullptr)
		, m_SwapChain(nullptr)
		, m_BackBuffer(nullptr)
		, m_DefaultRenderTarget(nullptr)
	{}

	void CleanupResources();

	bool CreateBackBuffer();
	bool CreateRenderTargetView();
	bool CreateDeviceAndSwapChain();

	void SetViewport(int x, int y, int width, int height, float minDepth, float maxDepth);
	void ClearBackbuffer(float colour[4]);
	void PresentBackbuffer();
	void ResizeBackbuffers(int width, int height);

	ID3D11Device*			GetDevice() const { return m_Device; }
	ID3D11DeviceContext*	GetDeviceContext() const { return m_DeviceContext; }


private:


private:

	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_DeviceContext;
	IDXGISwapChain*			m_SwapChain;
	ID3D11Texture2D*		m_BackBuffer;
	ID3D11RenderTargetView* m_DefaultRenderTarget;
};

void D3D11RenderBackend::CleanupResources()
{
	SAFE_RELEASE(m_DefaultRenderTarget);
	SAFE_RELEASE(m_BackBuffer);
	SAFE_RELEASE(m_SwapChain);
	SAFE_RELEASE(m_DeviceContext);
	SAFE_RELEASE(m_Device);

}

void D3D11RenderBackend::ClearBackbuffer(float colour[4])
{
	m_DeviceContext->ClearRenderTargetView(m_DefaultRenderTarget, colour);
}

void D3D11RenderBackend::PresentBackbuffer()
{
	m_SwapChain->Present(0, 0);
}

bool D3D11RenderBackend::CreateBackBuffer()
{
	// Get a pointer to the back buffer
	ID3D11Texture2D* pBackBuffer = nullptr;
	HRESULT res = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (res != S_OK)
	{
		CleanupResources();
		return false;
	}
	m_BackBuffer = pBackBuffer;
	return true;
}

bool D3D11RenderBackend::CreateRenderTargetView()
{
	// Create the default render tagrget view
	ID3D11RenderTargetView* pRtView = nullptr;
	HRESULT res = m_Device->CreateRenderTargetView(m_BackBuffer, nullptr, &pRtView);
	if (res != S_OK)
	{
		CleanupResources();
		return false;
	}
	m_DefaultRenderTarget = pRtView;

	// Set the new view as the render target
	m_DeviceContext->OMSetRenderTargets(1, &m_DefaultRenderTarget, nullptr);

	return true;
}

bool D3D11RenderBackend::CreateDeviceAndSwapChain()
{
	ID3D11Device *pDevice = nullptr;
	ID3D11DeviceContext *pDeviceContext = nullptr;
	IDXGISwapChain *pSwapChain = nullptr;
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1 };

	DXGI_SWAP_CHAIN_DESC scDesc;
	ZeroMemory(&scDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = Width;
	scDesc.BufferDesc.Height = Height;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = GetActiveWindow();
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = TRUE;

	auto createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr,					// adapter. Use default.
									D3D_DRIVER_TYPE_HARDWARE,	//
									nullptr,					// Don't need the software module when using DRIVER_TYPE_HARDWARE
									createDeviceFlags,			// Flags
									featureLevels,				// Array of feature levels to try to initiate
									1,							// 1 feature level in the array
									D3D11_SDK_VERSION,			// SDK version
									&scDesc,
									&pSwapChain,
									&pDevice,					// Pointer to the new device
									nullptr,					// We dont care about which feature level succeeded 
									&pDeviceContext				// The returned device context
									
	);

	if (res != S_OK)
	{
		// Something went wrong so free the resources
		CleanupResources();
		return false;
	}
	m_Device = pDevice;
	m_DeviceContext = pDeviceContext;
	m_SwapChain = pSwapChain;

	// Create the back buffer
	if (!CreateBackBuffer())
	{
		CleanupResources();
		return false;
	}

	// Create the render target view
	if (!CreateRenderTargetView())
	{
		CleanupResources();
		return false;
	}

	return true;
}


void D3D11RenderBackend::SetViewport(int x, int y, int width, int height, float minDepth, float maxDepth)
{
	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = minDepth;
	vp.MaxDepth = maxDepth;
	vp.TopLeftX = (float)x;
	vp.TopLeftY = (float)y;
	m_DeviceContext->RSSetViewports(1, &vp);
}

void D3D11RenderBackend::ResizeBackbuffers(int width, int height)
{
	// Set the new view as the render target
	m_DeviceContext->OMSetRenderTargets(0, 0, 0);
	SAFE_RELEASE(m_DefaultRenderTarget);
	SAFE_RELEASE(m_BackBuffer);
	HRESULT res = m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
	assert(res == S_OK);

	if (!CreateBackBuffer() || !CreateRenderTargetView())
	{
		//TODO: log an error
		return;
	}

	return;
}


class SDLApp
{
public:
	SDLApp()
		: m_Window(nullptr)
		, m_IsRunning(true)
	{}

	~SDLApp()
	{
		CleanUp();
		SDL_Quit();
	}

	int32 Initialise(D3D11RenderBackend* renderBackend, ImGuiWrapperD3D11* gui)
	{
		// Initialise all of the SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			SDL_LogError(0, "Could not intialise DSL library: %s", SDL_GetError());
			return 1;
		}

		// Create the window
		auto createWindowFlags = 
			SDL_WINDOW_RESIZABLE |
			SDL_WINDOW_SHOWN;
		m_Window = SDL_CreateWindow("WorldBuilder v0.000000000001", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, createWindowFlags);
		if (!m_Window)
			return 1;

		m_RenderBackend = renderBackend;
		m_Gui = gui;

		// Create the device and backends
		if (!m_RenderBackend->CreateDeviceAndSwapChain())
		{
			SDL_LogError(0, "Error trying to initialise D3D11 render backend. Exiting...");
			return 1;
		}

		// Initialise the gui
		m_Gui->Init(m_RenderBackend->GetDevice(), m_RenderBackend->GetDeviceContext(), GetActiveWindow());

		return 0; //OK
	}


	void HandleEvents()
	{
		auto windowId = SDL_GetWindowID(m_Window);
		SDL_Event event;
		SDL_PollEvent(&event);

		m_Input.ResetMouseKeys();
		m_Input.UpdateMousePos();

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			{
				if (event.button.button == SDL_BUTTON_LEFT) m_Input.SetMouseKeyDown(InputTracker::MouseButton::Left);
				if (event.button.button == SDL_BUTTON_RIGHT) m_Input.SetMouseKeyDown(InputTracker::MouseButton::Right);
				if (event.button.button == SDL_BUTTON_MIDDLE) m_Input.SetMouseKeyDown(InputTracker::MouseButton::Middle);
				return;
			}
		case  SDL_WINDOWEVENT:
			{
				if (event.window.windowID == windowId)
				{
					if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						OnResize();
					}
				}
				return;
			}

		// Handle the quitting event
		case SDL_QUIT:
			{
				m_IsRunning = false;
				return;
			}

		// Default case, do nothing
		default:
			break;
		}
	}

	void OnResize()
	{
		int width;
		int height;
		SDL_GetWindowSize(m_Window, &width, &height);

		// Update the gui


		// Remake the backbuffer
		m_RenderBackend->ResizeBackbuffers(width, height);
		m_RenderBackend->SetViewport(0, 0, width, height, 0.0f, 1.0f);		
	}
	
	void CleanUp()
	{
		if (m_Window)
			SDL_DestroyWindow(m_Window);

		m_Window = nullptr;
	}

	bool IsRunning() const { return m_IsRunning; }

	const InputTracker& GetInput() const { return m_Input; }

	SDL_Window* GetWindow() const { return m_Window; }

private:
	SDL_Window*				m_Window;
	D3D11RenderBackend*		m_RenderBackend;
	ImGuiWrapperD3D11*		m_Gui;
	InputTracker			m_Input; // Little container to store input state
	bool					m_IsRunning;
};


// Main entry function
int main(int argc, char *argv[])
{
	// Create an SDL app
	SDLApp app; 
	D3D11RenderBackend rbe;
	ImGuiWrapperD3D11 gui;

	// Initialise SDL, window, renderer, etc...
	app.Initialise(&rbe, &gui);

	// Set the full viewport
	rbe.SetViewport(0, 0, Width, Height, 0.0f, 1.0f);

	// Begin the main loop
	while (app.IsRunning())
	{

		app.HandleEvents();
		int w = 0;
		int h = 0;
		SDL_GetWindowSize(app.GetWindow(), &w, &h);
		gui.NewFrame(app.GetInput(), w, h);
		
		gui.MakeGui();

		// Do the familiar blue fade to illustrate the render backend is working correctly
		static float fade = 0.5f;
		float rate = 0.0001f;
		static float dir = rate;
		if (fade >= 1.0f) dir = -rate;
		if (fade <= 0.4f) dir = rate;
		fade += dir;

		// Clear the back baffer to our fade colour
		float colour1[] = { 0,0,fade,1 };
		rbe.ClearBackbuffer(colour1);

		gui.Render();
		rbe.PresentBackbuffer();
	}

	// Cleanup app resources
	app.CleanUp();

    return 0;
}

