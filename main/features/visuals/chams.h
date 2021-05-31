#pragma once
#include "../../common.h"
#include "../../core/interfaces.h"

class chams : public singleton<chams>
{
public:
	bool on_draw_model(model_render* ecx, void* edx, void* context, const draw_model_state& state, const model_render_info& info, matrix3x4_t* bone_to_world);
};