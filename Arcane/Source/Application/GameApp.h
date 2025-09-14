#pragma once
#include "Engine/GameEngine.h"

#ifdef ARC_APPLICATION_EXPORT
#define ARC_APPLICATION_API __declspec(dllexport)
#else
#define ARC_APPLICATION_API __declspec(dllimport)
#endif // ARC_APPLICATION_EXPORT

namespace arc
{
	class ARC_APPLICATION_API GameApplication : public IGameEngineAppInterface
	{
	protected:
		std::unique_ptr<GameEngine> mGameEngine;
	public:
		GameApplication();
		virtual ~GameApplication();

		void Run();
	protected:
		virtual void Create() override;
		virtual void Destroy() override;
		virtual void Tick(f32 deltaTime) override;
	};
}