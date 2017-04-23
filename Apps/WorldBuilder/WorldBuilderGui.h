#pragma once

#include "../../External/IMgui/imgui.h" //TODO: Add to the paths

namespace Pandora
{

class InputTracker;
class WorldBuilderGui
{
public:
	WorldBuilderGui() {}
	virtual ~WorldBuilderGui() {};

	void NewFrame(const InputTracker &input, int width, int height);
	void MakeGui();

private:
};

} //namespace Pandora