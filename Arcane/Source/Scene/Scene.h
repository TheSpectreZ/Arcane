#pragma once
#include "Core/Core.h"
#include "Core/Buffer.h"

#ifdef ARC_SCENE_EXPORT
#define ARC_SCENE_API __declspec(dllexport)
#else
#define ARC_SCENE_API __declspec(dllimport)
#endif // ARC_SCENE_EXPORT

namespace arc
{
	enum class EIdentifierType
	{
		Component, 
		Entity, 
		World
	};

	template<std::integral T, EIdentifierType Type> 
	struct EIdentifier
	{
		static EIdentifierType GetType() const { return Type; }

		T value = UINT64_MAX;
		
		EIdentifier& operator=(const EIdentifier<T, Type>& Other)
		{
			value = Other.value;
			return *this;
		}

		operator bool() { return IsValid(); }
		operator bool() const { return IsValid(); }

		bool IsValid() const
		{
			return value != UINT64_MAX;
		}

		bool operator==(const EIdentifier& other) const noexcept
		{
			return value == other.value && GetType() == other.GetType();
		}

		struct HASH
		{
			u64 operator()(const EIdentifier& type) const noexcept
			{
				return type.value;
			}
		};
	};

	using ComponentID	= EIdentifier<u64, EIdentifierType::Component>;
	using EntityID		= EIdentifier<u64, EIdentifierType::Entity>;
	
	class ARC_SCENE_API Entity
	{
		friend class EntityWorld;
	public:
		Entity() = default;
		virtual ~Entity() = default;

		EntityID GetID() const { return mId; }

		template<typename T>
		ComponentID AddComponent(T value)
		{
			return AddComponent(get_type<T>(), (void*)&value);
		}

		template<typename T>
		void RemoveComponent(ComponentID Id)
		{
			return RemoveComponent(get_type<T>());
		}

		template<typename T>
		void IterateComponent(std::function<void(T&)> func)
		{

		}

		ComponentID AddComponent(Type type, void* pData);
		
		void RemoveComponent(Type type, ComponentID Id);

		void IterateComponent(Type type, std::function<void(void*)> func);
	private:
		class EntityWorld* pWorld = nullptr;
		EntityID mId;
	};
	
	class ARC_SCENE_API EntityWorld
	{
		friend class Entity;
	public:
		EntityWorld();
		virtual ~EntityWorld();

		Entity CreateEntity();

		void DestroyEntity(Entity pEntity);
		void DestroyEntity(EntityID Id);

		template<typename T>
		TMemorySpan<T> GetComponents()
		{
			auto& buffer = GetComponentBuffer(get_type<T>());
			return TMemorySpan<T>(buffer.mData, buffer.mElementCount);
		}
	protected:
		ComponentID AddComponent(EntityID entity, Type type, void* pData);
		void RemoveComponent(EntityID entity, ComponentID Id);

		RawArrayBuffer& GetComponentBuffer(Type type);
	private:
		struct IMPL;
		IMPL* mImpl = nullptr;
	};

}