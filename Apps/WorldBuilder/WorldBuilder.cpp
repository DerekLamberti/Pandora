// WorldBuilder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../../Libraries/Base/Base.h"

#include <SDL.h>

using namespace Pandora;
class SDLApp
{
public:
	SDLApp()
		: m_Window(nullptr)
		, m_Surface(nullptr)
		, m_Renderer(nullptr)
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
		m_Window = SDL_CreateWindow("WorldBuilder v0.000000000001", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 200, SDL_WINDOW_SHOWN);
		if (!m_Window)
			return 1;

		// Create the surface
		m_Surface = SDL_GetWindowSurface(m_Window);
		if (!m_Surface)
			return 1;

		// Create the SDL 2D renderer
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (!m_Renderer)
			return 1;

		return 0; //OK
	}

	void Render()
	{
		if (!m_Renderer)
			return;

		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);

		// Clear to current draw colour
		SDL_RenderClear(m_Renderer);

		// Present to the window
		SDL_RenderPresent(m_Renderer);

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

		if (m_Renderer)
			SDL_DestroyRenderer(m_Renderer);

		m_Window = nullptr;
		m_Renderer = nullptr;
	}

	bool IsRunning() const { return m_IsRunning; }

private:
	SDL_Window*		m_Window;
	SDL_Surface*	m_Surface;
	SDL_Renderer*	m_Renderer;

	bool			m_IsRunning;
};


// Main entry function
int main(int argc, char *argv[])
{
	// Create an SDL app
	SDLApp app; 

	// Initialise SDL, window, renderer, etc...
	app.Initialise();

	// Begin the main loop
	while (app.IsRunning())
	{
		app.HandleEvents();

		app.Render();
	}

	// Cleanup app resources
	app.CleanUp();

    return 0;
}

