/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:41:38 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/25 10:41:40 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shader.hpp"

 Shader::Shader(): 	m_fragShaderPath(""), m_vertShaderPath(""),
					m_fragShaderCode(""), m_vertShaderCode("")

 {

 }

 Shader::~Shader()
 {
 	clear();
 }

void 	Shader::load(std::string const & vertPath, std::string const & fragmPath)
{
	m_vertShaderPath = vertPath;
	m_fragShaderPath = fragmPath;

	//std::cout << "readSources()" << std::endl;
	readSources();
	//std::cout << "createShader" << std::endl;
	createShader(m_vertShaderCode, GL_VERTEX_SHADER, m_vertShader);
	//std::cout << "createShader" << std::endl;
	createShader(m_fragShaderCode, GL_FRAGMENT_SHADER, m_fragShader);
	//std::cout << "createProgram" << std::endl;
	createProgram();
}

void 		Shader::readSources()
{
	std::ifstream vertexShader;
	std::ifstream fragmentShader;
	vertexShader.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fragmentShader.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertexShader.open(m_vertShaderPath);
		fragmentShader.open(m_fragShaderPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vertexShader.rdbuf();
		fShaderStream << fragmentShader.rdbuf();

		vertexShader.close();
		fragmentShader.close();

		m_vertShaderCode = vShaderStream.str();
		m_fragShaderCode = fShaderStream.str();
		std::cout <<"vert shader is\n" << m_vertShaderCode << "\n" << "frag shader is\n" << m_fragShaderCode << std::endl;
	}
	catch(std::ifstream::failure &e)
	{
		throw CustomException(std::string("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n"));
	}
}

void 		Shader::createShader(std::string const & shaderCode, GLenum shaderType, GLuint & shader)
{
	const char* src = shaderCode.c_str();
	///std::cout << "createShader_0" << std::endl;
	shader = glCreateShader(shaderType);
	//m_vertShader = glCreateShader(GL_VERTEX_SHADER);
	//std::cout << "createShader_0_1" << std::endl;
	glShaderSource(shader, 1, &src, nullptr);
	//std::cout << "createShader_0_2" << std::endl;
	glCompileShader(shader);
	//std::cout << "createShader_0_3" << std::endl;
	if (!isShaderCompiled(shader, 512, m_infolog)){
		std::string error;
		switch (shaderType){
			case GL_VERTEX_SHADER:
				error = std::string("VERTEX_SHADER::COMPILATION ");
				break;
			case GL_FRAGMENT_SHADER:
				error = std::string("FRAGMENT_SHADER::COMPILATION ");
				break;
			default:
				break;
		}
		throw CustomException(error + m_infolog);
	}
}


bool 		Shader::isShaderCompiled(GLuint shader, int infoSize, char *infoText) const
{
	int shaderCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
	if (!shaderCompiled)
		glGetShaderInfoLog(shader, infoSize, nullptr, infoText);
	return shaderCompiled != 0;
}


void 		Shader::createProgram()
{
	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertShader);
	glAttachShader(m_program, m_fragShader);
	glLinkProgram(m_program);
	if (!isProgramLinked(m_program, 512, m_infolog))
		throw CustomException(std::string("PROGRAM::LINKING ") + m_infolog);

	glDeleteShader(m_vertShader);
	glDeleteShader(m_fragShader);
}

bool 		Shader::isProgramLinked(GLuint program, int infoSize, char *infoText) const
{
	int programLinked;
	glGetProgramiv(program, GL_COMPILE_STATUS, &programLinked);
	if (!programLinked)
		glGetProgramInfoLog(program, infoSize, nullptr, infoText);
	return programLinked != 0;
}

void Shader::use()
{
	glUseProgram(m_program);
}

void Shader::clear()
{
	m_fragShaderPath = "";
	m_vertShaderPath = "";
	m_fragShaderCode = "";
	m_vertShaderCode = "";
	glDeleteProgram(m_program);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_program, name.c_str()), x, y);
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_program, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_program, name.c_str()), x, y, z, w);
}
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
