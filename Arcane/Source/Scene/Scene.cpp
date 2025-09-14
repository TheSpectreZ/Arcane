#include "Scene.h"

namespace arc
{
	class ComponentStorage : public RawArrayBuffer
	{
	public:
		ComponentStorage() = default;
		ComponentStorage(u64 elementSize) { Initialize(elementSize, 4); }

		ComponentID insert(void* pData)
		{
			ComponentID Id = get_component_id();
			insert_data(Id.value, pData);
			return Id;
		}

		void erase(ComponentID Id)
		{
			clear_component_id(Id);
			erase_data(Id.value);
		}
	private:
		ComponentID get_component_id()
		{
			return ComponentID
			{
				.value = mElementIndex++
			};
		}

		void clear_component_id(ComponentID Id)
		{

		}

		void insert_data(u64 Index, void* pData)
		{
			memcpy(mData + Index, pData, mElementStride);
		}

		void erase_data(u64 Index)
		{
			memset(mData + Index, 0, mElementStride);
		}
	private:
		TArrayBuffer<ComponentID> mFreeIndices;
	};

	////////////////////////////////////////////////////////////////////////

	struct EntityComponentList
	{
		std::unordered_set<ComponentID> component;
	};

	struct EntityWorld::IMPL
	{
		std::unordered_map<EntityID, EntityComponentList, EntityID::HASH> entities;
		std::unordered_map<Type, ComponentStorage, Type::HASH> storage;

		EntityID entityId = { 0 };

		EntityID NewEntityId()
		{
			return EntityID
			{
				.value = entityId.value++
			};
		}

		ComponentStorage& GetComponentStorage(Type type)
		{
			if (!storage.contains(type))
			{
				storage[type] = ComponentStorage(type.size);
			}

			return storage.at(type);
		}
	};

	EntityWorld::EntityWorld()
		:mImpl(new IMPL)
	{}
	
	EntityWorld::~EntityWorld()
	{
		delete mImpl;
	}

	//

	Entity EntityWorld::CreateEntity()
	{
		Entity newEntity;
		newEntity.mId = mImpl->NewEntityId();
		newEntity.pWorld = this;

		return newEntity;
	}

	void EntityWorld::DestroyEntity(Entity pEntity)
	{
		DestroyEntity(pEntity.mId);
	}

	void EntityWorld::DestroyEntity(EntityID Id)
	{
		// clear components
	}

	//
	
	ComponentID EntityWorld::AddComponent(EntityID entity, Type type, void* pData)
	{
		ComponentStorage& storage = mImpl->GetComponentStorage(type);
		
		auto componentId = storage.insert(pData);
		if (componentId)
		{
			mImpl->entities[entity].component.insert(componentId);
		}

		return componentId;
	}
	
	void EntityWorld::RemoveComponent(EntityID entity, ComponentID Id)
	{
		if (!mImpl->entities.contains(entity))
			return;
		
		mImpl->entities.at(entity).component.erase(Id);
	}

	RawArrayBuffer& EntityWorld::GetComponentBuffer(Type type)
	{
		return mImpl->GetComponentStorage(type);
	}

	////////////////////////////////////////////////////////////////////////

	ComponentID Entity::AddComponent(Type type, void* pData)
	{
		return pWorld->AddComponent(mId, type, pData);
	}

	void Entity::RemoveComponent(Type type, ComponentID Id)
	{
		pWorld->RemoveComponent(mId, Id);
	}

	void Entity::IterateComponent(Type type, std::function<void(void*)> func)
	{
	}
}
