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
		clear();
		std::cout <<  e.what() 	<< std::endl;
	}
}


ParticleSystemApplication::~ParticleSystemApplication()
{
	std::cout << "destructor\n";
	clear();
}

void 		ParticleSystemApplication::init()
{
	/*m_model = new Model();
	m_view = new View(m_model.get());*/
	m_model = std::make_unique<Model>();
	m_view = std::make_unique<View>(m_model.get());
	m_model->initModel();
	//m_controller = new Controller(m_model.get(),m_view.get());
	m_controller = std::make_unique<Controller>(m_model.get(),m_view.get());
}

void 		ParticleSystemApplication::clear()
{
	/*try {
		std::cout << "delete m_view\n";
		if (m_view)
			delete m_view;
			std::cout << "m_controller\n";
			if (m_controller)
			delete m_controller;
			std::cout << "m_model\n";
			if (m_model)
				delete m_model;
			} catch (std::exception & e) {
				std::cout <<  e.what() 	<< std::endl;
			}*/
}

void 		ParticleSystemApplication::run()
{
	std::cout << "run\n";
	m_controller->liveCycle();
}
