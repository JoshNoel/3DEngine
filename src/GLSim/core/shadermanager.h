#ifndef OGL_SHADERMANAGER_INCLUDED
#define OGL_SHADERMANAGER_INCLUDED

#include "GL/glew.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace ogs { class ShaderManager; }
class ShaderManager
{
public:
	enum SHADER_TYPE
	{
		VERTEX = 0,
		FRAGMENT = 1,
		GEOMETRY = 2
	};
	ShaderManager();
	~ShaderManager();

	bool addShader(SHADER_TYPE type, std::string path, unsigned int pass);
	bool linkProgram(unsigned int pass);
	bool useProgram(int pass);
	void unbindProgram();

	void setUniform(const std::string&, float);
	void setUniform(const std::string&, int);
	void setUniform(const std::string&, const glm::vec3&);
	void setUniform(const std::string&, const glm::vec4&);
	void setUniform(const std::string&, const glm::mat4&);

private:
	std::unordered_map<unsigned int, GLuint> m_programMap;
	std::unordered_map<unsigned int, std::unordered_map<SHADER_TYPE, GLuint>> m_shaderMap;

	unsigned int highestPass = 0;
	GLuint m_currentProgram = 0;
};
#endif
