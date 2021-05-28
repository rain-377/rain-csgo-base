#include "common.h"
#include "sdk/netvars/netvars.h"
#include "utils/render.h"
#include "utils/config.h"
#include "core/interfaces.h"
#include "core/hooks.h"

DWORD WINAPI Main(LPVOID lpParameter)
{
	while (!GetModuleHandle(SERVERBROWSER))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	if (!interfaces::setup() || !netvars::setup() || !input::setup() || !hooks::setup() || !config::setup())
		FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_FAILURE);

	while (!GetAsyncKeyState(VK_DELETE))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	hooks::restore();
	input::restore();
	render::restore();

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule, 
	DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		if (const auto handle = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main), hModule, 0, 0))
			CloseHandle(handle);

		return TRUE;
	}

	return FALSE;
}

