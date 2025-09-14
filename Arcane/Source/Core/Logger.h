#pragma once
#include "Base.h"
#include "Utility.h"

#ifdef ARC_CORE_EXPORT
#define ARC_CORE_API __declspec(dllexport)
#else
#define ARC_CORE_API __declspec(dllimport)
#endif // ARC_CORE_EXPORT

namespace arc
{
	class ARC_CORE_API Logger
	{
	public:
		Logger() = default;
		virtual ~Logger() = default;
		
		virtual void Log(const std::string& str) = 0;
	};

	class ARC_CORE_API ConsoleLogger : public Logger
	{
	public:
		ConsoleLogger();
		virtual ~ConsoleLogger() override = default;
	
		void Log(const std::string& str) override;
	};

	class ARC_CORE_API LogManager
	{
	private:
		LogManager() = default;

		std::list< unique<Logger> > mLoggerList;
	public:
		~LogManager() = default;

		LogManager(const LogManager&) = delete;
		LogManager& operator=(const LogManager&) = delete;

		LogManager(LogManager&&) = delete;
		LogManager& operator=(LogManager&&) = delete;

		static LogManager& Instance();
		
		template<typename T> requires std::derived_from<T, Logger>
		void Register()
		{
			mLoggerList.emplace_back(MakeUnique<T>());
		}

		template<typename... Args>
		void LOG(const char* Tag, const char* FILE, i32 LINE, const std::format_string<Args...>& fmt, Args&&... args)
		{
			auto UserMsg = std::format(fmt, std::forward<Args>(args)...);
			auto LogMsg  = std::format("[{}] - {}:{} {}", Tag, FILE, LINE, UserMsg.c_str());

			for (const auto& logger : mLoggerList)
				logger->Log(LogMsg);
		}
	};
}

#define LOGGER arc::LogManager::Instance()

#define ARC_LOG(Tag, Fmt, ... ) LOGGER.LOG(Tag, __FILE__, __LINE__, Fmt, __VA_ARGS__)