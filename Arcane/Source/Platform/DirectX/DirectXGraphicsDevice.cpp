#include "GraphicsDevice.h"
#include "DirectXGraphicsDevice.h"

namespace arc
{
	void D3D12GraphicsDevice::Setup(const GraphicsDeviceSetupInfo& Info)
	{
	}
}

namespace arc::graphics_device
{
	struct D3D12Context : IContext
	{
		D3D12Context()
		{
			SetContext(this);
		}

		std::unique_ptr<GraphicsDevice> create_device() override
		{
			return std::make_unique<D3D12GraphicsDevice>();
		}
	};

	static D3D12Context sContext;

	u32 ArcDirectXVersion()
	{
		return 1;
	}
}