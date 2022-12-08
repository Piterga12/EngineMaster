#ifndef _MODULE_DEBUGDRAW_H_
#define _MODULE_DEBUGDRAW_H_

#include "Module.h"
#include "..\libs\MathGeoLib\Include\Math\float4x4.h"

class DDRenderInterfaceCoreGL;

class ModuleDebugDraw : public Module
{

public:

    ModuleDebugDraw();
    ~ModuleDebugDraw();

	bool Init();
	update_status Update();
	bool CleanUp();
    void Draw(const float4x4& i_view, const float4x4& i_proj, unsigned i_width, unsigned i_height);
private:

    static DDRenderInterfaceCoreGL* implementation;
};

#endif /* _MODULE_DEBUGDRAW_H_ */
