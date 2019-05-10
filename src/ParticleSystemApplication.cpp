/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystemApplication.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:33:57 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:33:59 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParticleSystemApplication.hpp"

ParticleSystemApplication &   	ParticleSystemApplication::getInstance()
{
	static ParticleSystemApplication instance;
	return instance;
}

ParticleSystemApplication::ParticleSystemApplication() : m_isInit(false)
{
	try {
		init();
		m_isInit = true;
	} catch (std::exception &e) {
		std::cout <<  e.what() 	<< std::endl;
	}
}


ParticleSystemApplication::~ParticleSystemApplication()
{

}

void 		ParticleSystemApplication::init()
{
	m_model = new Model();
	m_view = std::make_unique<View>(m_model);
	m_model->initModel();
	m_controller = std::make_unique<Controller>(m_model,m_view.get());
}

void 		ParticleSystemApplication::run()
{
	m_controller->liveCycle();
}
