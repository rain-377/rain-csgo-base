#include "visuals.h"
#include "../../core/interfaces.h"
#include "../../utils/render.h"
#include "../../utils/config.h"
#include "../../global.h"

void visuals::on_paint()
{

	for (int i = 1; i < g_global_vars->m_max_clients; i++)
	{
		auto entity = reinterpret_cast<base_entity*>(g_entity_list->get_client_entity(i));
		if (!entity || entity->is_dormant() || !entity->is_player())
			continue;

		auto player = reinterpret_cast<cs_player*>(entity);
		if (!player->is_alive() || player == csgo::m_local)
			continue;

		auto bbox = get_bbox(entity);

		if (!bbox.empty())
		{
			if (config::get<bool>(HASH_CT("visuals.esp.name")))
			{
				std::string name = entity->get_info().m_name;
				if (entity->get_info().m_fakeplayer)
					name.append(" [bot]");

				render::text(name, ImVec2(bbox.x + bbox.w / 2, bbox.y - 16), ImColor(255, 255, 255), fonts::m_tahoma12, 12.f, FONT_OUTLINE | FONT_CENTERED_X);
			}
		
			if (config::get<bool>(HASH_CT("visuals.esp.health")))
			render::text(std::to_string(player->m_iHealth()), ImVec2(bbox.x - 10, bbox.y), ImColor(255, 255, 255), fonts::m_tahoma12, 12.f, FONT_OUTLINE | FONT_CENTERED_X | FONT_CENTERED_Y);
		}
	}
}

bbox visuals::get_bbox(base_entity* entity)
{
	vector_2d flb, brt, blb, frt, frb, brb, blt, flt;

	const auto& origin = entity->get_abs_origin();
	const auto min = entity->get_collideable()->get_obb_mins() + origin;
	const auto max = entity->get_collideable()->get_obb_maxs() + origin;

	vector points[] = 
	{
		vector(min.x, min.y, min.z),
		vector(min.x, max.y, min.z),
		vector(max.x, max.y, min.z),
		vector(max.x, min.y, min.z),
		vector(max.x, max.y, max.z),
		vector(min.x, max.y, max.z),
		vector(min.x, min.y, max.z),
		vector(max.x, min.y, max.z)
	};

	if (!render::world_to_screen(points[3], flb) || !render::world_to_screen(points[5], brt)
		|| !render::world_to_screen(points[0], blb) || !render::world_to_screen(points[4], frt)
		|| !render::world_to_screen(points[2], frb) || !render::world_to_screen(points[1], brb)
		|| !render::world_to_screen(points[6], blt) || !render::world_to_screen(points[7], flt))
		return { };

	vector_2d arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float x = flb.x;
	float y = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 1; i < 8; ++i)
	{
		if (x > arr[i].x)
			x = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (y > arr[i].y)
			y = arr[i].y;
	}

	bbox out;
	out.x = static_cast<int>(x);
	out.y = static_cast<int>(y);
	out.w = static_cast<int>(right - x);
	out.h = static_cast<int>(bottom - y);

	return out;
}