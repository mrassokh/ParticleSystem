/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:41:25 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/25 10:41:27 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include "GL/glew.h"

#include "glm/mat4x4.hpp"
#include "CustomExceptions.hpp"
//#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
	Shader();
	virtual ~Shader();

	void load(std::string const & vertPath, std::string const & fragmPath);
	void use();
	void clear();

	void setBool(const std::string &, bool ) const;
	void setInt(const std::string &, int ) const;
	void setFloat(const std::string &, float ) const;
	void setVec2(const std::string &, const glm::vec2 &) const;
	void setVec2(const std::string &, float, float) const;
	void setVec3(const std::string &, const glm::vec3 &) const;
	void setVec3(const std::string &, float, float, float) const;
	void setVec4(const std::string &, const glm::vec4 &) const;
	void setVec4(const std::string &, float, float, float, float) const;
	void setMat2(const std::string &, const glm::mat2 &) const;
	void setMat3(const std::string &, const glm::mat3 &) const;
	void setMat4(const std::string &, const glm::mat4 &) const;

private:
	void 			readSources();
	void 			createShader(std::string const & shaderCode, GLenum shaderType, GLuint & shader);
	void 			createProgram();
	bool 			isShaderCompiled(GLuint shader, int infoSize, char *infoText) const;
	bool 			isProgramLinked(GLuint program, int infoSize, char *infoText) const;

	char    		m_infolog[512];
    std::string 	m_fragShaderPath;
    std::string 	m_vertShaderPath;
    std::string 	m_fragShaderCode;
    std::string 	m_vertShaderCode;
    GLuint 			m_fragShader;
    GLuint 			m_vertShader;
	GLuint			m_program;
};

#endif /* end of include guard: SHADER_HPP
*/
