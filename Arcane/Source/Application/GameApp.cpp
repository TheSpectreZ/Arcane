#include "GameApp.h"

arc::GameApplication::GameApplication()
{
	mGameEngine = std::make_unique<GameEngine>();
}

arc::GameApplication::~GameApplication()
{
	mGameEngine.reset();
}

void arc::GameApplication::Run()
{
	GameEngineInfo engineInfo
	{
		.appInterface = this,
	};

	mGameEngine->Initialize(engineInfo);
	mGameEngine->Run();
	mGameEngine->Terminate();
}

/////////////////////////////////////////////

void arc::GameApplication::Create()
{
}

void arc::GameApplication::Destroy()
{
}

void arc::GameApplication::Tick(f32 deltaTime)
{
}
