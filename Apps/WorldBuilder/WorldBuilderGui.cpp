#include "stdafx.h"
#include "WorldBuilderGui.h"
#include "InputTracker.h"

#include <Windows.h>

namespace Pandora
{
	
void WorldBuilderGui::NewFrame(const InputTracker& input, int width, int height)
{
	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	io.DisplaySize = ImVec2((float)(width), (float)(height));

	// We call the DrawList function ourselves so make sure the callback is unset.
	io.RenderDrawListsFn = nullptr;

	// Mouse inputs
	io.MousePos = ImVec2((float)input.GetMouseX(), (float)input.GetMouseY());   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
	io.MouseDown[0] = input.IsLeftMouseDown();
	io.MouseDown[1] = input.IsRightMouseDown();
	io.MouseDown[2] = input.IsMiddleMouseDown();

	// Hide OS mouse cursor if ImGui is drawing it
	if (io.MouseDrawCursor)
		SetCursor(NULL);

	//// Setup time step
	//INT64 current_time;
	//QueryPerformanceCounter((LARGE_INTEGER *)&current_time);
	//io.DeltaTime = (float)(current_time - g_Time) / g_TicksPerSecond;
	//g_Time = current_time;

	//// Read keyboard modifiers inputs
	//io.KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
	//io.KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
	//io.KeyAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
	//io.KeySuper = false;
	//// io.KeysDown : filled by WM_KEYDOWN/WM_KEYUP events
	//// io.MousePos : filled by WM_MOUSEMOVE events
	//// io.MouseDown : filled by WM_*BUTTON* events
	//// io.MouseWheel : filled by WM_MOUSEWHEEL events

	// Now call down to the ImGui::NewFrame()
	ImGui::NewFrame();
}

void WorldBuilderGui::MakeGui()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Import model"))
		{
			// TODO: Import a 3D model from a file
		}


		if (ImGui::MenuItem("Exit"))
		{
			// Fixme: This should exit via the app exit function so cleanup can happen.
			exit(1);
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("About"))
		{
			// TODO: blurb.
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	// Create a sample panel
	{
		ImGui::Begin("test");
		ImGui::Text("Hello, world!");
		ImGui::End();
	}
}



} // namespace Pandora