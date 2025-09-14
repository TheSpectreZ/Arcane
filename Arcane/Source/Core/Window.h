#pragma once
#include "Core.h"

namespace arc
{
	struct AppWindowInfo
	{
		u32 width, height;
		cstring title;
	};

	class ARC_CORE_API AppWindow
	{
	protected:
		AppWindow() = default;
	public:
		virtual ~AppWindow() = default;

		virtual u64 GetHandle() const = 0;
	};

	struct IAppWindowInterface
	{
		virtual void OnWindowCreate(AppWindow* pWindow) = 0;
		virtual void OnWindowDestroy(AppWindow* pWindow) = 0;
	};

	namespace window
	{
		shared<AppWindow> ARC_CORE_API Create(const AppWindowInfo& Info, IAppWindowInterface* pInterface = nullptr);

		void ARC_CORE_API Tick();
	}
}