#include "render.h"
#include "../features/features.h"
#include "../core/interfaces.h"

void render::setup(IDirect3DDevice9* pDevice)
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(input::m_hwnd);
	ImGui_ImplDX9_Init(g_direct_device);

	m_draw_list = std::make_shared<ImDrawList>(ImGui::GetDrawListSharedData());
	m_data_draw_list = std::make_shared<ImDrawList>(ImGui::GetDrawListSharedData());
	m_replace_draw_list = std::make_shared<ImDrawList>(ImGui::GetDrawListSharedData());

	auto& io = ImGui::GetIO();
	auto& style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(500, 450);

	ImFontConfig tahoma14;
	tahoma14.RasterizerFlags = ImGuiFreeType::ForceAutoHint;
	fonts::m_tahoma14 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14.f, &tahoma14, io.Fonts->GetGlyphRangesCyrillic());

	ImFontConfig tahoma12;
	tahoma12.RasterizerFlags = ImGuiFreeType::MonoHinting | ImGuiFreeType::Monochrome;
	fonts::m_tahoma12 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 12.f, &tahoma12, io.Fonts->GetGlyphRangesCyrillic());

	ImGuiFreeType::BuildFontAtlas(io.Fonts);

	m_initialized = true;
}

void render::restore()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void render::text(std::string_view txt, ImVec2 pos, const ImColor& clr, ImFont* font, float font_size, uint8_t flags) {
	if ((flags & FONT_CENTERED_X) || (flags & FONT_CENTERED_Y))
	{
		const auto text_size = get_text_size(txt, font);

		if (flags & FONT_CENTERED_X)
		pos.x -= text_size.x / 2.f;

		if (flags & FONT_CENTERED_Y)
		pos.y -= text_size.y / 2.f;

	}

	m_draw_list->PushTextureID(font->ContainerAtlas->TexID);

	if (flags & FONT_DROPSHADOW) 
	{
		m_draw_list->AddText(font, font_size, pos + ImVec2(1.0f, 1.0f), ImColor(0, 0, 0, 255), txt.data());
	}
	if (flags & FONT_OUTLINE)
	{
		m_draw_list->AddText(font, font_size, pos + ImVec2(1.f, 0.f), ImColor(0, 0, 0, 255), txt.data());
		m_draw_list->AddText(font, font_size, pos + ImVec2(0.f, 1.0f), ImColor(0, 0, 0, 255), txt.data());
		m_draw_list->AddText(font, font_size, pos - ImVec2(1.f, 0.f), ImColor(0, 0, 0, 255), txt.data());
		m_draw_list->AddText(font, font_size, pos - ImVec2(0.f, 1.f), ImColor(0, 0, 0, 255), txt.data());
	}

	m_draw_list->AddText(font, font_size, pos, clr, txt.data());

	m_draw_list->PopTextureID();
}

void render::add_to_draw_list()
{
	const auto lock = std::unique_lock<std::mutex>(m_mutex, std::try_to_lock);
	if (lock.owns_lock()) 
	{
		*m_replace_draw_list = *m_data_draw_list;
	}

	*ImGui::GetBackgroundDrawList() = *m_replace_draw_list;
}

void render::begin()
{
	
	m_draw_list->Clear();
	m_draw_list->PushClipRectFullScreen();

	text("rain-csgo-base", ImVec2(10, 20), ImColor(255, 255, 255), fonts::m_tahoma12, 12.f, FONT_OUTLINE);

	visuals::get().on_paint();

	const auto lock = std::unique_lock<std::mutex>(m_mutex);

	*m_data_draw_list = *m_draw_list;
}

bool render::world_to_screen(vector& in, vector_2d& out)
{
	static auto& matrix = g_engine_client->world_to_screen_matrix();

	out.x = matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3];
	out.y = matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3];

	auto w = matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3];
	if (w < 0.001f)
	{
		out.x *= 100000.f;
		out.y *= 100000.f;
		return false;
	}

	out.x /= w;
	out.y /= w;

	int width, height;
	g_engine_client->get_screen_size(width, height);

	out.x = (width / 2.0f) + (out.x * width) / 2.0f;
	out.y = (height / 2.0f) - (out.y * height) / 2.0f;

	return true;
}
