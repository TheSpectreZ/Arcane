#pragma once
#include "Core.h"

namespace arc
{
	struct InputAction
	{

	};

	struct InputActionSet
	{

	};

	struct InputSpecification
	{
		std::unordered_map<std::string, InputActionSet> actionSet;
	};

	class ARC_CORE_API InputManager
	{
	protected:
		InputManager() = default;

		std::unordered_map<std::string, InputActionSet> actionSetMap;
	public:
		virtual ~InputManager() = default;
		
		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;

		InputManager(InputManager&&) = delete;
		InputManager& operator=(InputManager&&) = delete;

		virtual void Initialize(const InputSpecification& Specification) = 0;
		virtual void Tick() = 0;
	};

	namespace input_manager
	{
		unique<InputManager> ARC_CORE_API Create();
	}
}