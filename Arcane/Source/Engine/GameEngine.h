#pragma once
#include "Core/Window.h"
#include "Core/Input.h"

#ifdef ARC_ENGINE_EXPORT
#define ARC_ENGINE_API __declspec(dllexport)
#else
#define ARC_ENGINE_API __declspec(dllimport)
#endif // ARC_ENGINE_EXPORT

namespace arc
{
	struct IGameEngineAppInterface
	{
		virtual void Create() = 0;
		virtual void Destroy() = 0;
		virtual void Tick(f32 deltaTime) = 0;
	};

	struct GameEngineInfo
	{
		IGameEngineAppInterface* appInterface;
	};

	class ARC_ENGINE_API GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void Initialize(const GameEngineInfo& Info);
		void Run();
		void Terminate();
		
		void Shutdown();

		void CreateAppWindow(const AppWindowInfo& Info);
	private:
		struct IMPL;
		IMPL* mImpl = nullptr;

		IGameEngineAppInterface* mAppInterface = nullptr;
	};
}