#ifndef OGL_GLOBALSETTINGS_INCLUDED
#define OGL_GLOBALSETTINGS_INCLUDED

#include <string>

namespace ogl
{
	static enum DEFAULT_TAGS
	{
		TAG_DEFAULT,
		TAG_CAMERA
	};
	static std::vector<std::string> tags =
	{
		"Default",
		"Camera"
	};
}

#endif