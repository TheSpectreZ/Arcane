#pragma once
#include "Graphics/GraphicsDevice.h"

#ifdef ARC_VULKAN_EXPORT
#define ARC_VULKAN_API __declspec(dllexport)
#else
#define ARC_VULKAN_API __declspec(dllimport)
#endif // ARC_VULKAN_EXPORT

namespace arc
{
	class ARC_VULKAN_API VulkanGraphicsDevice : public GraphicsDevice
	{
	public:
		VulkanGraphicsDevice() = default;
		~VulkanGraphicsDevice() override = default;

		virtual void Setup(const GraphicsDeviceSetupInfo& Info) override;
	};

	namespace graphics_device
	{
		extern "C" ARC_VULKAN_API u32 ArcVulkanVersion();
	}
}