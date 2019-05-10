/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:11:44 by mrassokh          #+#    #+#             */
/*   Updated: 2019/02/25 12:11:47 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParticleManager.hpp"

ParticleManager::ParticleManager()
{
	m_CLE = std::shared_ptr<CLEngine>(CLEngine::getInstance());
}


ParticleManager::~ParticleManager()
{
	m_particleSystems.clear();
}

void 		ParticleManager::init()
{
	auto infoMap = RESOURCE.getParticleInfoMap();
	try {
		for (auto & infoElement : infoMap) {
			auto type = infoElement.first;
			auto info = infoElement.second;
			addParticleSystem(type, info, INIT_PARTICLE_COUNT);
		}
	} catch (CustomException &ex) {
		std::cout << ex.what() << std::endl;
		exit(42);
	}
}

void 			ParticleManager::addParticleSystem(psType const type, psInfo const &info, int const particleCount)
{
	psPtr particleSystem = PARTICLE_CREATOR.createParticleSystem(type, m_CLE, info, particleCount);
	m_particleSystems.push_back(particleSystem);
}

void 			ParticleManager::startDrawPS(psType const type)
{
	auto ps = m_particleSystems[type];
	if (ps->isRunning())
		return;
	ps->start();
}

void 				ParticleManager::startCurrentParticleSystem(psType const type)
{
	auto ps = m_particleSystems[type];
	if (ps->isRunning())
		return;
	ps->start();
}

void 				ParticleManager::stopCurrentParticleSystem(psType const type)
{
	auto ps = m_particleSystems[type];
	ps->stop();
}


void 				ParticleManager::reinitCurrentParticleSystem(psType const type, int const particleCount)
{
	auto ps = m_particleSystems[type];
	ps->stop();
	ps->clearMemoryStack();
	ps->setParticleCount(particleCount);
	auto info = RESOURCE.getParticleInfo(type);
	ps->createGLBufers();
	ps->initGLBufers(info.initName);
}

void 				ParticleManager::updateCurrentParticleSystem(psType const type, glm::vec3 const & gravityCenter, bool isGravityActive)
{
	if (m_particleSystems[type]->chekLiveTime()) {
		m_particleSystems[type]->updateGLBufers(m_particleSystems[type]->getUpdateKernelName(), gravityCenter, isGravityActive);
	}
}
