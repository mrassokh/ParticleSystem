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
	void 						draw(glm::mat4 const & projection, glm::mat4 const & view);
	int & 						getCurrentParticleSystemCount(int n) {
									if (n < m_particleSystems.size()) {
										return m_particleSystems[n]->getParticleCount();
									}
									//return 0;
								};


private:
	std::shared_ptr<CLEngine> 	m_CLE;
	ParticleSystems				m_particleSystems;

	void 						addParticleSystem(psType const type, psInfo const &info);
};

#endif
