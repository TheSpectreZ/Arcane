#include "Input.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GameInput.h>

namespace arc
{
	static u32 GetDeviceUID(const APP_LOCAL_DEVICE_ID& id)
	{
		u32 uid = 0;
		std::memcpy(&uid, id.value, sizeof(uid));
		return uid;
	}

	class IInputdevice
	{
	protected:
		IGameInput* mHandler = nullptr;
		IGameInputDevice* mDevice = nullptr;

		u32 mDeviceId = 0;
	public:
		IInputdevice(IGameInput* pHandler, IGameInputDevice* pDevice)
			:mHandler(pHandler), mDevice(pDevice) 
		{
			mDeviceId = GetDeviceUID(mDevice->GetDeviceInfo()->deviceId);
		}

		virtual ~IInputdevice() = default;

		virtual void Update() = 0;
	};

	///////////////////////////////////////////////

	class KeyboardInputDevice : public IInputdevice
	{
	public:
		KeyboardInputDevice(IGameInput* pHandler, IGameInputDevice* pDevice) : IInputdevice(pHandler, pDevice) {}

		void Update() override
		{
			IGameInputReading* pReading = nullptr;
			if (SUCCEEDED(mHandler->GetCurrentReading(GameInputKindKeyboard, mDevice, &pReading)))
			{
				
			}
		}
	};

	///////////////////////////////////////////////
	
	class MouseInputDevice : public IInputdevice
	{
	public:
		MouseInputDevice(IGameInput* pHandler, IGameInputDevice* pDevice) : IInputdevice(pHandler, pDevice) {}

		void Update() override
		{
			IGameInputReading* pReading = nullptr;
			if (SUCCEEDED(mHandler->GetCurrentReading(GameInputKindMouse, mDevice, &pReading)))
			{
				GameInputMouseState state{};
				if (pReading->GetMouseState(&state))
				{
					if (state.buttons != GameInputMouseNone)
					{
						//ARC_LOG("Input", "Mouse {}: dx={}, dy={}, buttons={}", mDeviceId, state.positionX, state.positionY, (i32)state.buttons);
					}
				}
				pReading->Release();
			}
		}
	};

	///////////////////////////////////////////////

	class Win32InputManager : public InputManager
	{
		IGameInput* mGameInputHandle = nullptr;

		std::unordered_map<u32, std::unique_ptr<IInputdevice>> mInputDeviceList;
	public:
		Win32InputManager()
		{
			ARC_ASSERT(SUCCEEDED(GameInputCreate(&mGameInputHandle)));

			mGameInputHandle->RegisterDeviceCallback(nullptr, GameInputKindKeyboard, GameInputDeviceAnyStatus, GameInputBlockingEnumeration, this, &KeyboardDeviceCallback, nullptr);
			mGameInputHandle->RegisterDeviceCallback(nullptr, GameInputKindMouse   , GameInputDeviceAnyStatus, GameInputBlockingEnumeration, this, &MouseDeviceCallback, nullptr);

			mGameInputHandle->RegisterReadingCallback(nullptr, GameInputKindKeyboard, 0.f, this, &KeyboardReadingCallback, nullptr);
			mGameInputHandle->RegisterReadingCallback(nullptr, GameInputKindMouse	, 0.f, this, &MouseReadingCallback, nullptr);
		}

		~Win32InputManager() override
		{
			mGameInputHandle->Release();
		}

		void Initialize(const InputSpecification& Specs) override
		{
			actionSetMap = Specs.actionSet;
		}

		void Tick() override
		{
			for (const auto& [deviceId, device] : mInputDeviceList)
			{
				device->Update();
			}
		}

		////////////////////////////////////////

		static void KeyboardDeviceCallback(GameInputCallbackToken callbackToken, void* context, IGameInputDevice* device, uint64_t timestamp, GameInputDeviceStatus currentStatus, GameInputDeviceStatus previousStatus)
		{
			auto InputMan = reinterpret_cast<Win32InputManager*>(context);

			if ((currentStatus & GameInputDeviceConnected) != 0)
			{
				auto deviceId = GetDeviceUID(device->GetDeviceInfo()->deviceId);
				InputMan->mInputDeviceList[deviceId] = std::make_unique<KeyboardInputDevice>(InputMan->mGameInputHandle, device);
			}
		}

		static void MouseDeviceCallback(GameInputCallbackToken callbackToken, void* context, IGameInputDevice* device, uint64_t timestamp, GameInputDeviceStatus currentStatus, GameInputDeviceStatus previousStatus)
		{
			auto InputMan = reinterpret_cast<Win32InputManager*>(context);

			if ((currentStatus & GameInputDeviceConnected) != 0)
			{
				auto deviceId = GetDeviceUID(device->GetDeviceInfo()->deviceId);
				InputMan->mInputDeviceList[deviceId] = std::make_unique<MouseInputDevice>(InputMan->mGameInputHandle, device);;
			}
		}

		////////////////////////////////////////

		static void KeyboardReadingCallback(GameInputCallbackToken callbackToken, void* context, IGameInputReading* reading, bool hasOverrunOccurred)
		{
			auto InputMan = reinterpret_cast<Win32InputManager*>(context);
		}
		
		static void MouseReadingCallback(GameInputCallbackToken callbackToken, void* context, IGameInputReading* reading, bool hasOverrunOccurred)
		{
			auto InputMan = reinterpret_cast<Win32InputManager*>(context);
		}
	};
}

namespace arc
{
	unique<InputManager> input_manager::Create()
	{
		return MakeUnique<Win32InputManager>();
	}
}