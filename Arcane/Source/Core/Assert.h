#pragma once
#include "Type.h"

#include <format>

#ifdef ARC_CORE_EXPORT
#define ARC_CORE_API __declspec(dllexport)
#else
#define ARC_CORE_API __declspec(dllimport)
#endif // ARC_CORE_EXPORT

namespace arc
{
	void ARC_CORE_API Assert(cstring reason);
}

#define __ARC_ASSERT(cond, msg, ...)  if(!(cond)) { arc::Assert(std::format(msg, __VA_ARGS__).c_str()); }