#include "GraphicsDevice.h"
#include "VulkanGraphicsDevice.h"

namespace arc
{
	void VulkanGraphicsDevice::Setup(const GraphicsDeviceSetupInfo& Info)
	{
	}
}

namespace arc::graphics_device
{
	struct VulkanContext : IContext
	{
		VulkanContext()
		{
			SetContext(this);
		}

		std::unique_ptr<GraphicsDevice> create_device() override
		{
			return std::make_unique<VulkanGraphicsDevice>();
		}
	};

	VulkanContext sContext;

	u32 ArcVulkanVersion()
	{
		return 1;
	}
}