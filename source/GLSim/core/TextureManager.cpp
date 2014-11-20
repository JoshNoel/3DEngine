#include "GLSim/core/TextureManager.h"
#include "FreeImage.h"

TextureManager::TextureManager()
{ }

TextureManager::~TextureManager()
{ }

int TextureManager::LoadTexture(const std::string& path, TEXTURE_TYPE type, int numMipMaps)
{
	FIBITMAP* bitmap;
	GLuint tex;
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str());
	if (format == FIF_UNKNOWN)
	{
		fprintf(stdout, "Image file format not supported: %s\n", path.c_str());
		return -1;
	}
	bitmap = FreeImage_Load(format, path.c_str());
	if (!bitmap)
	{
		fprintf(stdout, "Image file could not be loaded: %s\n", path.c_str());
		return -1;
	}
	FIBITMAP* temp = FreeImage_ConvertTo32Bits(bitmap);
	if (!bitmap)
	{
		fprintf(stdout, "Image file could not be converted to 32bits: %s\n", path.c_str());
		return -1;
	}
	FreeImage_Unload(bitmap);
	bitmap = temp;


	glGenTextures(1, &tex);
	//todo: Allow different texture types
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexStorage2D(GL_TEXTURE_2D, numMipMaps, GL_RGBA8, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap));
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), GL_RGBA8, 
		//GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));

	glBindTexture(GL_TEXTURE_2D, 0);

	if(m_openID == -1)
	{
		int index = m_lastID;
		m_textureMap.emplace(m_lastID, tex);
		m_lastID++;
		return index;
	}
	else
	{
		int index = m_openID;
		m_textureMap.emplace(m_openID, tex);
		m_openID = -1;
		return index;

	}
}

GLuint TextureManager::getTexture(int index)
{
	return m_textureMap.at(index);
}

std::unordered_map<int, GLuint> TextureManager::m_textureMap;
int TextureManager::m_lastID = 0;
int TextureManager::m_openID = -1;