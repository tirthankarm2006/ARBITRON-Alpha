#pragma once

namespace ARB {
	class Log
	{
	public:
		Log(std::string name);
	private:
		std::shared_ptr<spdlog::logger> logger;
	};
}

