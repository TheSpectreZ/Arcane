#pragma once
#include "Graphics/GraphicsDevice.h"

#ifdef ARC_DIRECTX_EXPORT
#define ARC_DIRECTX_API __declspec(dllexport)
#else
#define ARC_DIRECTX_API __declspec(dllimport)
#endif

namespace arc
{
	class ARC_DIRECTX_API D3D12GraphicsDevice : public GraphicsDevice
	{
	public:
		D3D12GraphicsDevice() = default;
		~D3D12GraphicsDevice() override = default;

		virtual void Setup(const GraphicsDeviceSetupInfo& Info) override;
	};

	namespace graphics_device
	{
		extern "C" ARC_DIRECTX_API u32 ArcDirectXVersion();
	}
}