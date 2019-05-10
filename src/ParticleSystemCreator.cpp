/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystemCreator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:50:14 by mrassokh          #+#    #+#             */
/*   Updated: 2019/03/02 11:50:15 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParticleSystemCreator.hpp"

ParticleSystemCreator & ParticleSystemCreator::getInstance()
{
	static ParticleSystemCreator instance;
	return instance;
}

ParticleSystemCreator::ParticleSystemCreator()
{
	m_createFunctions.push_back(&ParticleSystemCreator::createParticleSystemPoint);
	m_createFunctions.push_back(&ParticleSystemCreator::createParticleSystemCube);
	m_createFunctions.push_back(&ParticleSystemCreator::createParticleSystemPoint);
	m_createFunctions.push_back(&ParticleSystemCreator::createParticleSystemCube);
}

ParticleSystemCreator::~ParticleSystemCreator()
{
	m_createFunctions.clear();
}


psPtr 	ParticleSystemCreator::createParticleSystem(psType type, clePtr clEngine, psInfo const & info, int const particleCount) const

{
	return (this->*m_createFunctions[type])(clEngine, info, particleCount);
}

psPtr 	ParticleSystemCreator::createParticleSystemPoint(clePtr clEngine, psInfo const & info, int const particleCount) const
{
	psPtr psPoint = std::make_shared<ParticleSystemPoint>();
	initParticleSystem(psPoint, clEngine, info, particleCount);
	return psPoint;
}

psPtr 	ParticleSystemCreator::createParticleSystemCube(clePtr clEngine, psInfo const & info, int const particleCount) const
{
	psPtr psCube = std::shared_ptr<ParticleSystem>(new ParticleSystemPoint());
	initParticleSystem(psCube, clEngine, info, particleCount);
	return psCube;
}

void 	ParticleSystemCreator::initParticleSystem(psPtr particleSystem, clePtr clEngine, psInfo const & info, int const particleCount) const
{
	particleSystem->setCLEngine(clEngine);
	particleSystem->setParticleCount(particleCount);
	particleSystem->setCLContext();
	particleSystem->setShader(info.shaderName);
	particleSystem->setInitKernelName(info.initName);
	particleSystem->setUpdateKernelName(info.updateName);
	particleSystem->createGLBufers();
	particleSystem->initGLBufers(info.initName);
	particleSystem->setliveTime(info.liveTime);
}
