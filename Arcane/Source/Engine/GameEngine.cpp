#include "GameEngine.h"

#include "Graphics/GraphicsDevice.h"

namespace arc
{
	namespace link_resolver
	{

#if GRAPHICS_OPENGL
		extern "C" _declspec(dllimport) u32 ArcOpenGLVersion();
		u32 graphicsVersion = ArcOpenGLVersion();
#elif GRAPHICS_VULKAN
		extern "C" _declspec(dllimport) u32 ArcVulkanVersion();
		u32 graphicsVersion = ArcVulkanVersion();
#elif GRAPHICS_DIRECTX
		extern "C" __declspec(dllimport) u32 ArcDirectXVersion();
		u32 graphicsVersion = ArcDirectXVersion();
#else
		#error "No Graphics API Implementation Found"
#endif

	}
}

namespace arc
{
	struct GameEngine::IMPL : IAppWindowInterface
	{
		std::list< std::shared_ptr<AppWindow> > windowList;

		std::unique_ptr<InputManager> inputManager;

		std::unique_ptr<GraphicsDevice> graphicsDevice;
		
		bool IsActive() const
		{
			return !windowList.empty();
		}

		void Shutdown()
		{
			windowList.clear();
		}
		
		// IAppWindowInterface
		
		void OnWindowCreate(AppWindow* pWindow) override
		{
			graphicsDevice->CreateContext(pWindow);
		}

		void OnWindowDestroy(AppWindow* pWindow) override
		{
			for (auto Iter = windowList.begin(); Iter != windowList.end(); Iter++)
			{
				if (Iter->get() == pWindow)
				{
					graphicsDevice->DestroyContext(pWindow);
					windowList.erase(Iter);
					break;
				}
			}
		}
	};

	///////////////////////////////////////////////////

	GameEngine::GameEngine()
	{
		LOGGER.Register<ConsoleLogger>();

		mImpl = new IMPL();
		mImpl->inputManager   = input_manager::Create();
		mImpl->graphicsDevice = graphics_device::Create();
	}
	
	GameEngine::~GameEngine()
	{
		delete mImpl;
	}

	void GameEngine::Initialize(const GameEngineInfo& Info)
	{
		mAppInterface = Info.appInterface;

		if (mAppInterface)
		{
			mAppInterface->Create();
		}
	}

	void GameEngine::Run()
	{
		while (mImpl->IsActive())
		{
			window::Tick();

			mImpl->inputManager->Tick();

			if (mAppInterface)
				mAppInterface->Tick(0.f);

			mImpl->graphicsDevice->Tick();
		}
	}

	void GameEngine::Terminate()
	{
		if (mAppInterface)
			mAppInterface->Destroy();
	}

	///////////////////////////////////////////////////

	void GameEngine::Shutdown()
	{
		mImpl->Shutdown();
	}

	void GameEngine::CreateAppWindow(const AppWindowInfo& Info)
	{
		mImpl->windowList.push_back(window::Create(Info, mImpl));
	}
}