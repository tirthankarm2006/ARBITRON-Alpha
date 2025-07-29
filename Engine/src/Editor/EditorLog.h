#pragma once

namespace ARB {
	namespace Editor {
		class Log
		{
		public:
			Log(std::string name);
			std::shared_ptr<spdlog::logger> logger;
		private:
			std::shared_ptr<spdlog::sinks::wincolor_stdout_sink_mt>sink;
		};
	}
}

