#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <vector>

#include "Errors.h"

class Shader
{
public:
	Shader();
	~Shader();

	void compileShader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	void linkShaders();

	void addAttribute(const std::string& attributeName);
	GLint getUniformLocation(const std::string& uniformName);
	void use();
	void unuse();

private:
	void compileShader(const std::string& filePath, GLuint shaderId);

	GLuint m_programID;
	GLuint m_vertexID;
	GLuint m_fragmentID;

	int m_numAttributes;
};

#endif  //SHADER_H