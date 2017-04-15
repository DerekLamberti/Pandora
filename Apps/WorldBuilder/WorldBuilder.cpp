// WorldBuilder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

	bool CreateDeviceAndSwapChain();
	void SetViewport(int x, int y, int width, int height, float minDepth, float maxDepth);
	void ClearBackbuffer(float colour[4]);
	void PresentBackbuffer();


private:
	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_DeviceContext;
	IDXGISwapChain*			m_SwapChain;
	ID3D11Texture2D*		m_BackBuffer;
	ID3D11RenderTargetView* m_DefaultRenderTarget;
};

void D3D11RenderBackend::ClearBackbuffer(float colour[4])
{
	m_DeviceContext->ClearRenderTargetView(m_DefaultRenderTarget, colour);
}

void D3D11RenderBackend::PresentBackbuffer()
{
	m_SwapChain->Present(0, 0);
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

	HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr,					// adapter. Use default.
									D3D_DRIVER_TYPE_HARDWARE,	//
									nullptr,					// Don't need the software module when using DRIVER_TYPE_HARDWARE
									0,							// Flags
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
		SAFE_RELEASE(pDevice);
		SAFE_RELEASE(pDeviceContext);
		SAFE_RELEASE(pSwapChain);
		return false;
	}

	// Get a pointer to the back buffer
	ID3D11Texture2D* pBackBuffer = nullptr;
	res = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (res != S_OK)
	{
		SAFE_RELEASE(pDevice);
		SAFE_RELEASE(pDeviceContext);
		SAFE_RELEASE(pSwapChain);
		SAFE_RELEASE(pBackBuffer);
		return false;
	}

	// Create the default render tagrget view
	ID3D11RenderTargetView* pRtView = nullptr;
	res = pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRtView);
	if (res != S_OK)
	{
		SAFE_RELEASE(pDevice);
		SAFE_RELEASE(pDeviceContext);
		SAFE_RELEASE(pSwapChain);
		SAFE_RELEASE(pBackBuffer);
		SAFE_RELEASE(pRtView);
	}

	// Set the new view as the render target
	pDeviceContext->OMSetRenderTargets(1, &pRtView, nullptr);

	// Set the member variables
	m_Device = pDevice;
	m_DeviceContext = pDeviceContext;
	m_SwapChain = pSwapChain;
	m_BackBuffer = pBackBuffer;
	m_DefaultRenderTarget = pRtView;

	return true;
}

void D3D11RenderBackend::SetViewport(int x, int y, int width, int height, float minDepth, float maxDepth)
{
	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = minDepth;
	vp.MaxDepth = maxDepth;
	vp.TopLeftX = x;
	vp.TopLeftY = y;
	m_DeviceContext->RSSetViewports(1, &vp);
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

	int32 Initialise()
	{
		// Initialise all of the SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			SDL_LogError(0, "Could not intialise DSL library: %s", SDL_GetError());
			return 1;
		}

		// Create the window
		m_Window = SDL_CreateWindow("WorldBuilder v0.000000000001", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
		if (!m_Window)
			return 1;

		return 0; //OK
	}

	void HandleEvents()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		// Handle the quitting event
		if (event.type == SDL_QUIT)
		{
			m_IsRunning = false;
		}
	}
	
	void CleanUp()
	{
		if (m_Window)
			SDL_DestroyWindow(m_Window);

		m_Window = nullptr;
	}

	bool IsRunning() const { return m_IsRunning; }

private:
	SDL_Window*		m_Window;

	bool			m_IsRunning;
};


// Main entry function
int main(int argc, char *argv[])
{
	// Create an SDL app
	SDLApp app; 

	// Initialise SDL, window, renderer, etc...
	app.Initialise();

	// Initialise the render backend.
	D3D11RenderBackend rbe;
	if (!rbe.CreateDeviceAndSwapChain())
	{
		SDL_LogError(0, "Error trying to initialise D3D11 render backend. Exiting...");
		return 0;
	}

	// Set the full viewport
	rbe.SetViewport(0, 0, Width, Height, 0.0f, 1.0f);

	// Begin the main loop
	while (app.IsRunning())
	{
		app.HandleEvents();

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

		rbe.PresentBackbuffer();
	}

	// Cleanup app resources
	app.CleanUp();

    return 0;
}

