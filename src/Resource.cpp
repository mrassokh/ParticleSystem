/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Resource.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:34:21 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:34:23 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Resource.hpp"

Resource & 	Resource::getInstance()
{
	static Resource instance;
	return instance;
}

Resource::Resource()
{
	m_CLEngine = std::shared_ptr<CLEngine>(CLEngine::getInstance());
}


Resource::~Resource()
{
	m_shaderMap.clear();
	m_psInfoMap.clear();
}

void		Resource::loadShader(std::string const & vPath, std::string const & fPath, std::string const & name)
{

	shaderPtr shader = std::make_shared<Shader>();
	shader->load(vPath, fPath);
	m_shaderMap.emplace(name,shader);
}

void			Resource::addKernel(std::string const & srcPath, std::string const & srcName,
										std::string const & programName, std::string const & kernelName, std::string const & funcName)
{

	m_CLEngine->addProgramSource(srcPath, srcName);
	m_CLEngine->addProgramFromSource(srcName, programName);
	m_CLEngine->addKernel(programName, kernelName, funcName);
}

void 			Resource::initParticleInfo(psType type, std::string const & initName, std::string const & updateName,
														std::string const & shaderName, std::string const & textureName, float const liveTime)
{
	psInfo info;

	info.initName = initName;
	info.updateName = updateName;
	info.shaderName = shaderName;
	info.textureName = textureName;
	info.liveTime = liveTime;

	m_psInfoMap.emplace(type, info);
}

shaderPtr 			Resource::getShader(std::string const & name)
{
	auto shader = m_shaderMap.find(name);

	if (shader != m_shaderMap.end()) {
	   return shader->second;
   	} else {
		throw CustomException(" Shader " + name + " is not found");
	}
}

psInfo const &		Resource::getParticleInfo(psType type) const
{
	auto info = m_psInfoMap.find(type);

	if (info != m_psInfoMap.end()) {
	   return info->second;
   	} else {
		throw CustomException(" Info for type is not found");
	}
}
