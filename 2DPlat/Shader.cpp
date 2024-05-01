#include "Shader.h"

Shader::Shader() :
	m_programID(0),
	m_vertexID(0),
	m_fragmentID(0),
	m_numAttributes(0)
{}

Shader::~Shader()
{}

void Shader::compileShader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	m_programID = glCreateProgram();

	m_vertexID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexID == 0)
	{
		fatalError("Vertex shader failed to be created!");
	}

	m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentID == 0)
	{
		fatalError("Fragment shader failed to be created!");
	}

	compileShader(vertexFilePath, m_vertexID);
	compileShader(fragmentFilePath, m_fragmentID);

}

void Shader::linkShaders()
{
	
	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);

	glLinkProgram(m_programID);


	glDetachShader(m_programID, m_vertexID);
	glDetachShader(m_programID, m_fragmentID);

	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
}

void Shader::compileShader(const std::string& filePath, GLuint shaderId)
{
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail())
	{
		fatalError("Failed  to open " + filePath);
	}

	std::string fileContent = "";
	std::string line;

	while (std::getline(shaderFile, line))
	{
		fileContent += line + "\n";
	}

	shaderFile.close();

	const char* contentPtr = fileContent.c_str();
	glShaderSource(shaderId, 1, &contentPtr, nullptr);

	glCompileShader(shaderId);

	GLint success = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(shaderId);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Shader " + filePath + " failed to compile!");

	}
}

void Shader::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());

}

void Shader::use()
{
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void Shader::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + uniformName + " not found in shaders!");
	}

	return location;
}