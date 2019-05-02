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
const int INIT_PARTICLE_COUNT =  1000000;

typedef std::vector<psPtr> ParticleSystems;
/*typedef std::map<psType, psInfo> ParticleInfoMap;
typedef std::map<std::string,std::vector<glm::mat4>> ParticleSystemTransMap;*/

class ParticleManager{
public:
	ParticleManager();
	ParticleManager(ParticleManager const & rhs) = delete;
	ParticleManager & operator=(ParticleManager const & rhs) = delete;
	~ParticleManager();

	void 						init();
	ParticleSystems &			getParticleSystems() {return m_particleSystems;};
	void 						startDrawPS(psType const type);
	void 						startCurrentParticleSystem(INIT_MESH const type);
	void 						stopCurrentParticleSystem(INIT_MESH const type);
	void 						reinitCurrentParticleSystem(INIT_MESH const type, int const particleCount);
	void 						updateCurrentParticleSystem(INIT_MESH const type);
	psPtr						getCurrentParticleSystem(INIT_MESH const type) {return m_particleSystems[type];};

	void 						draw(glm::mat4 const & projection, glm::mat4 const & view);
	// int & 						getCurrentParticleSystemCount(int n) {
	// 								if (n < m_particleSystems.size()) {
	// 									return m_particleSystems[n]->getParticleCount();
	// 								}
	// 								//return 0;
	// 							};


private:
	std::shared_ptr<CLEngine> 	m_CLE;
	ParticleSystems				m_particleSystems;

	void 						addParticleSystem(psType const type, psInfo const &info,int const particleCount);
};

#endif
