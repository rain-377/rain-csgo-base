#pragma once
#include "../common.h"

class menu : public singleton<menu>
{
public:
	void on_paint();

	bool m_visible;
};