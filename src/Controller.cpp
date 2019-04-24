/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controller.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:36:45 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:36:46 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Controller.hpp"

Controller::Controller (Model *model, View	*view) : m_model(model), m_view(view)
{
	m_inputManager = std::make_unique<InputManager>();
}

void 		Controller::liveCycle()
{
	while (m_model->getIsRunning())
	{
		m_view->draw();
		//const SDL_Event e = m_view->getEvent();
		eventsAnalyses(m_inputManager->eventProcessing(m_view->getEvent()));
		//m_model->setIsRunning(false);
	}
}

void 		Controller::eventsAnalyses(Events const &ev)
{
	switch (ev) {
		case Events::FINISH:
		m_model->setIsRunning(false);
			break;
		default:
			break;
	}
}
