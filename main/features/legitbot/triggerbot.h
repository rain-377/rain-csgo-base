#pragma once
#include "../../common.h"
#include "../../core/interfaces.h"
#include "../../utils/math.h"
#include "../../global.h"

class triggerbot : public singleton<triggerbot>
{
public:
	void on_create_move(user_cmd* cmd);
};