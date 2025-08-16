#pragma once

#include "EditorLog.h"

namespace ARB {
	//To be created in Engine runtime
	class Profile
	{
	public:
		Profile(std::string profileLoc);
		std::string profileName;
		std::string profileLoc;
	private:
		std::shared_ptr<Editor::Log> profileLogger;
	};
}

