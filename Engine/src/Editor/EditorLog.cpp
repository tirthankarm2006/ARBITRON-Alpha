#include "ARBpch.h"
#include "EditorLog.h"

namespace ARB{
	namespace Editor {
		Log::Log(std::string name) {
			logger = std::make_shared<spdlog::logger>(name);
			logger->set_level(spdlog::level::trace);
			sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
			logger->sinks().push_back(sink);
			logger->set_pattern("[%n]%^[%l]:  %v%$ [%r]");
		}
	}
}