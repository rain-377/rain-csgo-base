#pragma once
#include "../common.h"
#include "../sdk/definitions.h"
#include "../sdk/datatypes/usercmd.h"
#include "interfaces.h"
#include "../core/menu.h"

namespace hooks
{
	bool setup();
	void restore();

	namespace create_move
	{
		bool __stdcall hooked(float input_sample_time, user_cmd* cmd);
		inline decltype(&hooked) original = nullptr;
	};

	namespace frame_stage_notify
	{
		void __stdcall hooked(client_frame_stage stage);
		inline decltype(&hooked) original = nullptr;
	};


	namespace reset
	{
		long __stdcall hooked(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
		inline decltype(&hooked) original = nullptr;
	};

	namespace end_scene
	{
		long __stdcall hooked(IDirect3DDevice9* pDevice);
		inline decltype(&hooked) original = nullptr;
	};

	namespace lock_cursor
	{
		void __fastcall hooked(surface* thisptr, int edx);
		inline decltype(&hooked) original = nullptr;
	};
};