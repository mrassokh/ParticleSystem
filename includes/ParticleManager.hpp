/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:12:09 by mrassokh          #+#    #+#             */
/*   Updated: 2019/02/25 12:12:11 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "CLEngine.hpp"
// #include "Shader.hpp"


#ifndef PARTICLE_MANAGER_HPP
#define PARTICLE_MANAGER_HPP
#include "ParticleSystem.hpp"
#include "ParticleSystemCreator.hpp"
#include "Resource.hpp"
const int INIT_PARTICLE_COUNT =  1000000;

typedef std::vector<psPtr> ParticleSystems;

class ParticleManager{
public:
	ParticleManager();
	ParticleManager(ParticleManager const & rhs) = delete;
	ParticleManager & operator=(ParticleManager const & rhs) = delete;
	~ParticleManager();

	void 						init();
	ParticleSystems &			getParticleSystems() {return m_particleSystems;};
	void 						startDrawPS(psType const type);
	void 						startCurrentParticleSystem(psType const type);
	void 						stopCurrentParticleSystem(psType const type);
	void 						reinitCurrentParticleSystem(psType const type, int const particleCount);
	void 						updateCurrentParticleSystem(psType const type, glm::vec3 const & gravityCenter, bool isGravityActive);
	psPtr &						getCurrentParticleSystem(psType const type) {return m_particleSystems[type];};

private:
	std::shared_ptr<CLEngine> 	m_CLE;
	ParticleSystems				m_particleSystems;

	void 						addParticleSystem(psType const type, psInfo const &info,int const particleCount);
};

#endif
