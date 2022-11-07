#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		MYLOG("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		MYLOG("Dummy CleanUp!");
		return true;
	}
};