#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		PERSLOG("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		PERSLOG("Dummy CleanUp!");
		return true;
	}
};