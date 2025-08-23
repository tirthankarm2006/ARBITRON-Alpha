#include "ARBpch.h"
#include "Log.h"

namespace ARB {
	Log::Log(std::string name) {
		logger = std::make_shared<spdlog::logger>(name);
	}
}