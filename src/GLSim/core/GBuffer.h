#ifndef OGL_GBUFFER_INCLUDED
#define OGL_GBUFFER_INCLUDED
#include "GL\glew.h"

class GBuffer
{
public:
	GBuffer(unsigned int width, unsigned int height);
	~GBuffer();

	enum GBUFFER_TEXTURE_TYPES
	{
		DIFFUSE,
		NORMAL,
		UV,
		POSITION
	};

	void bindRead();
	void bindDraw();
	void setReadBuffer(GBUFFER_TEXTURE_TYPES);

private:
	static const int NUM_TEXTURES = 4;
	//framebuffer
	GLuint m_fbo;
	//textures to render to
	//0 = Diffuse
	//1 = Normal
	//2 = UV
	//3 = Position
	GLuint m_textures[NUM_TEXTURES];
	//depth texture
	GLuint m_depth;
};

#endif

