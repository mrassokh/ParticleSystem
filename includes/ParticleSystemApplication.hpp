/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystemApplication.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:30:22 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:30:25 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PARTICLE_SYSTEM_APPLICATION
#define PARTICLE_SYSTEM_APPLICATION
#include "Controller.hpp"
#define PARTICLE_SYSTEM ParticleSystemApplication::getInstance()

class  ParticleSystemApplication {
public:
	static ParticleSystemApplication &  		getInstance();
	virtual ~ParticleSystemApplication();

	void 		run();
private:
	ParticleSystemApplication();
	ParticleSystemApplication(ParticleSystemApplication const & rhs) = delete;
	ParticleSystemApplication & operator = (ParticleSystemApplication const & rhs) = delete;

	void 		init();

	std::unique_ptr<View> 			m_view;
	std::unique_ptr<Controller> 	m_controller;
	Model 							*m_model;

	bool 		 					m_isInit;
};
#endif /* end of include guard: PARTICLE_SYSTEM_APPLICATION */
