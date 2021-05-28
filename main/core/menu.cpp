#include "menu.h"
#include "../utils/config.h"

void menu::on_paint()
{
	m_visible = input::get_key<TOGGLE>(VK_INSERT);
	if (!m_visible)
		return;

	if (ImGui::Begin("rain-csgo-base"), true)
	{
		ImGui::Checkbox("test checkbox", &config::get<bool>(HASH_CT("example.test_checkbox")));
		ImGui::SliderInt("test slider int", &config::get<int>(HASH_CT("example.test_slider_int")), 0, 100);
		ImGui::SliderFloat("test slider float", &config::get<float>(HASH_CT("example.test_slider_float")), 0.f, 100.f);
		ImGui::Combo("test combo", &config::get<int>(HASH_CT("example.test_combo")), "item 1\0item 2\0item 3\0\0");

		ImGui::Checkbox("name esp", &config::get<bool>(HASH_CT("visuals.esp.name")));
		ImGui::Checkbox("health esp", &config::get<bool>(HASH_CT("visuals.esp.health")));

		if (ImGui::Button("Load config"))
			config::load();

		if (ImGui::Button("Save config"))
			config::save();

		ImGui::End();
	}
}