#pragma once
#include "Type.h"

#include <concepts>
#include <typeindex>
#include <memory>

#ifdef ARC_CORE_EXPORT
#define ARC_CORE_API __declspec(dllexport)
#else
#define ARC_CORE_API __declspec(dllimport)
#endif // ARC_CORE_EXPORT

namespace arc
{
	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T, typename... Args>
	unique<T> MakeUnique(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T, typename... Args>
	shared<T> MakeShared(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	struct ARC_CORE_API Type
	{
		std::type_index index;
		u64 size;
		u64 alignment;

		bool operator==(const Type& other) const noexcept
		{
			return index == other.index && size == other.size && alignment == other.alignment;
		}

		struct HASH
		{
			u64 operator()(const Type& type) const noexcept
			{
				return type.index.hash_code();
			}
		};
	};

	template<typename T>
	Type get_type()
	{
		return Type
		{
			.index = std::type_index(typeid(T)),
			.size = sizeof(T),
			.alignment = alignof(T)
		};
	}

	template<typename T>
	T Min(T a, T b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	T Max(T a, T b)
	{
		return a > b ? a : b;
	}
}