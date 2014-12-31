#include "GBuffer.h"
#include <cstdlib>
#include <stdio.h>


GBuffer::GBuffer(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	//Generate render textures
	glGenTextures(NUM_TEXTURES, m_textures);
	for(int i = 0; i < NUM_TEXTURES; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
	}

	glGenTextures(1, &m_depth);
	glBindTexture(GL_TEXTURE_2D, m_depth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth, 0);

	GLenum bufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, bufs);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		fprintf(stdout, "Error creating framebuffer\n");
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}


GBuffer::~GBuffer()
{
	glDeleteFramebuffers(1, &m_fbo);
}

void GBuffer::bindRead()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
}

void GBuffer::bindDraw()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void GBuffer::setReadBuffer(GBUFFER_TEXTURE_TYPES type)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
}

const int GBuffer::NUM_TEXTURES;
