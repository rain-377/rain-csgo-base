#pragma once
#include "../common.h"
#include "../sdk/vector.h"

enum font_flags : unsigned int
{
	FONT_NONE = 0,
	FONT_DROPSHADOW = 1 << 0,
	FONT_OUTLINE = 1 << 1,
	FONT_CENTERED_X = 1 << 2,
	FONT_CENTERED_Y = 1 << 2,
};

namespace render
{
	void setup(IDirect3DDevice9* pDevice);
	void restore();
	void add_to_draw_list();
	void begin();
	void text(std::string_view txt, ImVec2 pos, const ImColor& clr, ImFont* font, float font_size, uint8_t flags);

	bool world_to_screen(vector& in, vector_2d& out);

	inline ImVec2 get_text_size(std::string_view text, ImFont* font) 
	{
		const auto size = font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.f, text.data());

		return size;
	}

	inline void text(std::string_view txt, vector pos, const ImColor& clr, ImFont* font, float font_size, uint8_t flags)
	{
		text(txt, ImVec2(pos.x, pos.y), clr, font, font_size, flags);
	}

	inline bool m_initialized = false;

	inline std::mutex m_mutex;

	inline std::shared_ptr<ImDrawList> m_draw_list;
	inline std::shared_ptr<ImDrawList> m_data_draw_list;
	inline std::shared_ptr<ImDrawList> m_replace_draw_list;
}

namespace fonts
{
	inline ImFont* m_tahoma12 = nullptr;
	inline ImFont* m_tahoma14 = nullptr;
}