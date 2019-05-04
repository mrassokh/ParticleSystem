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
	std::cout << "ParticleManager()" << std::endl;
	m_CLE = std::shared_ptr<CLEngine>(CLEngine::getInstance());
	std::cout << "m_CLE : " << m_CLE.get() << std::endl;
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
			//addParticleSystem(type, info, INIT_PARTICLE_COUNT);
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

void 			ParticleManager::draw(glm::mat4 const & projection, glm::mat4 const & view)
{
	//auto start = std::chrono::high_resolution_clock::now();
	std::vector<glm::mat4> transforms;
	for (int i = 0; i < 1; ++i){
				glm::mat4 model = glm::mat4(1.0f);
				//model =  glm::translate(model, glm::vec3(-2.5f, 0.0f, -2.5f));
				//model = glm::translate(model, glm::vec3(3.0f ,0.0f,2.0f* (i + 1)));
				transforms.push_back(model);
			}
	//int i = 0;
	for (auto & element : m_particleSystems) {
		//std::cout << "try draw element: " << element.first<<std::endl;
		//printf("draw element with %d",i++);
		auto & ps = element;
		if (ps->chekLiveTime()){
			// std::cout << "draw element: " << element.first<<std::endl;
			 auto start1 = std::chrono::high_resolution_clock::now();
			ps->updateGLBufers(ps->getUpdateKernelName());
			 auto end1 = std::chrono::high_resolution_clock::now();
		    std::chrono::duration<double> diff1 = end1-start1;
	  std::cout << "updateGLContent: "<<diff1.count()<<std::endl;

				//auto start = std::chrono::high_resolution_clock::now();
				//ps->drawGLContent(projection, view, transforms);
			// 	 auto end = std::chrono::high_resolution_clock::now();
			// 	std::chrono::duration<double> diff = end-start;
		   // std::cout << "drawGLContent: "<<diff.count()<<std::endl;
		}
	}

	// auto end = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> diff = end-start;
    // std::cout << "draw function: " << diff.count()<<std::endl;
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
		std::cout<< " RESOURCE.getParticleInfo\n";
	auto info = RESOURCE.getParticleInfo(type);
	ps->createGLBufers();
	ps->initGLBufers(info.initName);
}

void 				ParticleManager::updateCurrentParticleSystem(psType const type)
{
	if (m_particleSystems[type]->chekLiveTime()) {
		m_particleSystems[type]->updateGLBufers(m_particleSystems[type]->getUpdateKernelName());
		 std::cout << "updateGLContent: "<<std::endl;
	}
}
