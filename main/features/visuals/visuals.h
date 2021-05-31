#pragma once
#include "../../common.h"
#include "../../sdk/entity.h"

struct bbox
{
	int x, y, w, h;
	bbox() = default;
	bbox(const int x, const int y, const int w, const int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	inline bool empty() const { return x == 0.f && y == 0.f && w == 0.f && h == 0.f; }
};

class visuals : public singleton<visuals>
{
public:
	void on_paint();
private:
	bbox get_bbox(base_entity* ent);
};