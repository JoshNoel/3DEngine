#include "GLSim/core/shadermanager.h"
#include <iostream>
#include <fstream>

ShaderManager::ShaderManager()
	:m_programMap(),
	m_shaderMap()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::setUniform(const std::string& name, int n)
{
	int i = glGetUniformLocation(m_currentProgram, name.c_str());
	glUniform1i(glGetUniformLocation(m_currentProgram, name.c_str()), n);
}

void ShaderManager::setUniform(const std::string& name, float n)
{
	int i = glGetUniformLocation(m_currentProgram, name.c_str());

	glUniform1f(glGetUniformLocation(m_currentProgram, name.c_str()), n);
}

void ShaderManager::setUniform(const std::string& name, const glm::vec3& v)
{
	glUniform3fv(glGetUniformLocation(m_currentProgram, name.c_str()), 1, glm::value_ptr(v));
}

void ShaderManager::setUniform(const std::string& name, const glm::vec4& v)
{
	glUniform4fv(glGetUniformLocation(m_currentProgram, name.c_str()), 1, glm::value_ptr(v));
}

void ShaderManager::setUniform(const std::string& name, const glm::mat4& m)
{
	int i = glGetUniformLocation(m_currentProgram, name.c_str());
	glUniformMatrix4fv(glGetUniformLocation(m_currentProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

bool ShaderManager::useProgram(int pass)
{
	m_currentProgram = m_programMap.at(pass);
	if(m_programMap.at(pass) != NULL)
	{
		glUseProgram(m_currentProgram);
		return true;
	}
	return false;
}

void ShaderManager::unbindProgram()
{
	glUseProgram(0);
}

bool ShaderManager::addShader(SHADER_TYPE type, std::string path, unsigned int pass)
{
	fprintf(stdout, "Adding Shader to pass %u from: %s\n", pass, &path[0]);
	GLuint shaderID;

	if(m_programMap.find(pass) == m_programMap.end())
		m_programMap.emplace(pass, glCreateProgram());

	switch(type)
	{
	case VERTEX:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GEOMETRY:
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
	}

	std::ifstream is;
	std::string line = "";
	std::string file = "";
	is.open(path);
	if(!is.is_open())
	{
		fprintf(stdout, "Error opening shader at: %s\n", path);
		return false;
	}
	
	while(!is.eof())
	{
		std::getline(is, line);
		file += (line + "\n");
	}

	const GLchar *source = (const GLchar *)file.c_str();
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if(success != GL_TRUE)
	{

		GLint logLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

		GLchar errorLog[1024];
		glGetShaderInfoLog(shaderID, logLength, NULL, &errorLog[0]);

		fprintf(stdout, "Error compiling shader at: %s\n %s\n", path.c_str(), errorLog);

		glDeleteShader(shaderID);
		return false;
	}

	glAttachShader(m_programMap.at(pass), shaderID);
	if(m_shaderMap.find(pass) == m_shaderMap.end())
		m_shaderMap.emplace(pass, std::unordered_map<SHADER_TYPE, GLuint>());
	m_shaderMap.at(pass).emplace(type, shaderID);
	return true;
}

bool ShaderManager::linkProgram(unsigned int pass)
{
	GLuint programID = m_programMap.at(pass);
	glLinkProgram(programID);

	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if(linkStatus != GL_TRUE)
	{
		GLint logLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> errorLog(logLength);
		glGetProgramInfoLog(programID, logLength, NULL, &errorLog[0]);
		fprintf(stdout, "Error Linking Program for Pass %u\n %s", pass, &errorLog[0]);

		glDeleteProgram(programID);

		for(int i = 0; i < 3; ++i)
		{
			if(m_shaderMap.at(pass).find(SHADER_TYPE(i)) != m_shaderMap.at(pass).end())
			{
				glDeleteShader(m_shaderMap.at(pass).at(SHADER_TYPE(i)));
			}
		}
		return false;
	}

	for(int i = 0; i < 3; ++i)
	{
		if(m_shaderMap.at(pass).find(SHADER_TYPE(i)) != m_shaderMap.at(pass).end())
		{
			glDetachShader(m_programMap.at(pass), m_shaderMap.at(pass).at(SHADER_TYPE(i)));
			glDeleteShader(m_shaderMap.at(pass).at(SHADER_TYPE(i)));
		}
	}

	return true;
}