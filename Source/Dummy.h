#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		return true;
	}

	bool CleanUp()
	{
		return true;
	}
};