/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:51:59 by mrassokh          #+#    #+#             */
/*   Updated: 2019/03/01 13:52:02 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include "CLEngine.hpp"
#include "Shader.hpp"
#include "CustomExceptions.hpp"
#include "Resource.hpp"
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MVCBase.hpp"

# define LIVE_TIME 55.0f
# define LIVE_TIME_CLOUD 2000000.0f

struct Particle
{
	cl_float4	position;
	//cl_float4	velocity;
//	cl_float4	color;
};

const int particleCount = 1000000;
typedef std::chrono::time_point<std::chrono::high_resolution_clock>	t_point;

class ParticleSystem {
public:
	ParticleSystem();
	ParticleSystem(ParticleSystem const & rhs);
	ParticleSystem & operator = (ParticleSystem const & rhs);
	virtual ~ParticleSystem();

	std::string const & 		getInitKernelName() const;
	std::string const & 		getUpdateKernelName() const;
	int &						getParticleCount() {return m_particleCount;};
	float &						getLiveTime() {return m_liveTime;};
	GLuint 						getVAO() {return m_VAO;};
	GLuint 						getIBO() {return m_IBO;};
	std::shared_ptr<Shader> & 	getShader() {return m_shader;};
	void 						setInitKernelName(std::string const & initName);
	void 						setUpdateKernelName(std::string const & updateName);

	void 						setCLEngine(std::shared_ptr<CLEngine>);
	void 						setCLContext();
	void 						setParticleCount(int particleCount);
	void 						setShader(std::string shaderName);
	void 						setliveTime(float liveTime);

	void 						addGLBuffer(GLuint & vbo);
	void 						clearMemoryStack();
	std::vector<cl::Memory>  &  getMemoryStack();

	void 						start();
	void 						stop();
	bool						isRunning() const;
	bool 						chekLiveTime();


	virtual void				createGLBufers() = 0;
	virtual void 				setInstanceBuffer() = 0;
	virtual void 				setTexture(std::string const & textureName) = 0;
	virtual void 				initGLBufers(std::string const & initKernelName) = 0;
	virtual void 				updateGLBufers(std::string const & updateKernelName, glm::vec3 const & gravityCenter, bool isGravityActive) = 0;
	//virtual void				drawGLContent(glm::mat4 const & projection, glm::mat4  const & view, std::vector<glm::mat4> const & transforms) = 0;

protected:
	std::shared_ptr<CLEngine> 	m_CLE;
	std::shared_ptr<Shader> 	m_shader;
	std::string					m_initKernelName;
	std::string					m_updateKernelName;
	cl::Context 				m_context;
	std::vector<cl::Memory> 	m_memory;

	GLuint 						m_VBO;
	GLuint 						m_VAO;
	GLuint						m_IBO;

	int							m_particleCount;
	t_point						m_startTime;
	t_point						m_stepTime;
	float						m_deltaTime;
	float						m_totalTime;
	float						m_liveTime;
	bool						m_isRunning;
};

#endif
