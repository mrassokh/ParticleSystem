

#ifndef PARTICLE_SYSTEM_POINT_HPP
#define PARTICLE_SYSTEM_POINT_HPP

#include "CLEngine.hpp"
#include "Shader.hpp"
#include "CustomExceptions.hpp"
#include "Resource.hpp"
#include "ParticleSystem.hpp"

class ParticleSystemPoint : public ParticleSystem  {
public:
	ParticleSystemPoint();
	virtual ~ParticleSystemPoint();

	virtual void 		createGLBufers();
	virtual void 		setInstanceBuffer();
	virtual void 		setTexture(std::string const & textureName);
	virtual void 		initGLBufers(std::string const & initKernelName);
	virtual void 		updateGLBufers(std::string const & updateKernelName, glm::vec3 const & gravityCenter, bool isGravityActive);
};

#endif
