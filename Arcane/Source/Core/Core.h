#pragma once

#ifdef ARC_CORE_EXPORT
#define ARC_CORE_API __declspec(dllexport)
#else
#define ARC_CORE_API __declspec(dllimport)
#endif // ARC_CORE_EXPORT

#include "Base.h"
#include "Logger.h"
#include "Assert.h"
#include "Utility.h"

#define ARC_ASSERT(cond)  if(!(cond)) { ARC_LOG("ERROR", "{}", #cond); arc::Assert(std::format("{}", #cond).c_str()); }
#define ARC_ASSERT_MSG(cond, msg, ...)  if(!(cond)) { ARC_LOG("ERROR", msg, __VA_ARGS__); arc::Assert(std::format(msg, __VA_ARGS__).c_str()); }