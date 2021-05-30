#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <intrin.h>
#include <vector>
#include <optional>
#include <mutex>
#include <limits>
#include <unordered_map>
#include <any>
#include <filesystem>
#include <deque>
#include <d3d9.h>
#include <d3dx9.h>

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_freetype.h"

#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../dependencies/imgui/win32/imgui_impl_win32.h"

#include "utils/utils.h"
#include "utils/input.h"
#include "sdk/fnv1a.h"

#define SERVERBROWSER "serverbrowser.dll"
#define CLIENT "client.dll"
#define ENGINE "engine.dll"