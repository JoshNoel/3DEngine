#ifndef OGL_TEXTURE_MANAGER_INCLUDED
#define OGL_TEXTURE_MANAGER_INCLUDED

#include <string>
#include <unordered_map>
#include "GL/glew.h"


namespace ogl { class TextureManager; enum TEXTURE_TYPES; }

enum TEXTURE_TYPE
{
	TEXTURE_1D,
	TEXTURE_2D,
	TEXTURE_3D
};

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static int LoadTexture(const std::string& path, TEXTURE_TYPE, int numMipMaps = 3);
	static GLuint getTexture(int index);

private:
	//id, bitmap
	static std::unordered_map<int, GLuint> m_textureMap;
	static int m_lastID;
	static int m_openID;
};
#endif