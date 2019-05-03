/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Resource.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:32:39 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:32:41 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  RESOURCE_HPP
#define RESOURCE_HPP
#include "Shader.hpp"
#include "CLEngine.hpp"
#include "MVCBase.hpp"

typedef struct 				ParticleSystemInfo
{
	std::string   		initName;
	std::string   		updateName;
	std::string   		shaderName;
	std::string  		textureName;
	float				liveTime;
}							psInfo;

typedef std::map<psType, psInfo> ParticleInfoMap;


typedef std::shared_ptr<CLEngine> 						clePtr;
typedef std::map<std::string, std::shared_ptr<Shader>>	shadersMap;
typedef std::map<psType, psInfo> 						ParticleInfoMap;
typedef std::shared_ptr<Shader> 						shaderPtr;
#define RESOURCE Resource::getInstance()

class Resource {
public:
	static Resource & 		getInstance();

	clePtr 					getCLEngine() {return m_CLEngine;};
	shaderPtr 				getShader(std::string const & name);
	psInfo const &			getParticleInfo(psType type) const;
	ParticleInfoMap const &	getParticleInfoMap() const {return m_psInfoMap;};

	void		loadShader(std::string const & vPath, std::string const & fPath, std::string const & name);
	void		addKernel(std::string const & srcPath, std::string const & srcName,
											std::string const & programName, std::string const & kernelName, std::string const & funcName);
	void 		initParticleInfo(psType type, std::string const & initName, std::string const & updateName,
											std::string const & shaderName, std::string const & textureName, float const liveTime);

	virtual ~Resource();
private:
	Resource();
	//Resource(Resource const &) = delete;
	//Resource operator = (Resource const &) = delete;


	clePtr 						m_CLEngine;
	shadersMap 					m_shaderMap;
	ParticleInfoMap				m_psInfoMap;
};

#endif /* end of include guard: RESOURCE */
