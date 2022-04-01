#pragma once

#include <string>
#include <sstream>
#include <exception>
#include <typeinfo>
#include <type_traits>
#include <exception>
#include <memory>
#include <chrono>

#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <unordered_map>

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NODRAWTEXT
#define NOMINMAX
#include <Windows.h>

#include <comdef.h>
#include <atlbase.h>
#include <mmeapi.h>
#include <wincodec.h>
#include <d2d1.h>
#include <dwrite.h>
#include <dsound.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-gc.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/exception.h>