#include "GraphicsDevice.h"

namespace arc
{

}

namespace arc::graphics_device
{
	static IContext* gContext = nullptr;

	void SetContext(IContext* pInterface)
	{
		gContext = pInterface;
	}

	std::unique_ptr<GraphicsDevice> Create()
	{
		return gContext->create_device();
	}
}