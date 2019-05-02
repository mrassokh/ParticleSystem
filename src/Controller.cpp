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
		//m_model->draw();
		m_view->draw();
		//const SDL_Event e = m_view->getEvent();
		eventsAnalyses(m_inputManager->eventProcessing(m_view->getEvent()));
		imGuiEventsAnalyses(m_inputManager->imGuiEventProcessing(m_view->getImGuiEvent()));
		//m_model->setIsRunning(false);
	}
}

void 		Controller::eventsAnalyses(Events const &ev)
{
	mouseShiftCoord mouseShift;
	switch (ev) {
		case Events::FINISH:
			m_model->setIsRunning(false);
			break;
		case Events::FORWARD:
			m_model->cameraMoveForward(m_view->getDeltaTime());
			break;
		case Events::BACKWARD:
			m_model->cameraMoveBackward(m_view->getDeltaTime());
			break;
		case Events::RIGHT:
			m_model->cameraMoveRight(m_view->getDeltaTime());
			break;
		case Events::LEFT:
			m_model->cameraMoveLeft(m_view->getDeltaTime());
			break;
		case Events::ROTATE:
			mouseShift =  m_inputManager->getMouseShiftCoord();
			m_model->cameraRotate(mouseShift.x, mouseShift.y);
			break;
		case Events::CHANGE_CAMERA_MOVE_MODE:
			std::cout << "CHANGE_CAMERA_MOVE_MODE\n";
			m_model->changeIsCameraMoveMode();
			break;
		case Events::GRAVITY_ON:
			m_model->setIsGravityActive(true);
			m_model->setGravityCenter(m_inputManager->getXMouse(), m_inputManager->getYMouse(), m_view->getWidth(), m_view->getHeight());
			break;
		case Events::GRAVITY_OFF:
			m_model->setIsGravityActive(false);
			break;
		case Events::SET_GRAVITY_CENTER:
			m_model->setGravityCenter(m_inputManager->getXMouse(), m_inputManager->getYMouse(), m_view->getWidth(), m_view->getHeight());
			break;
		case Events::DROP_TO_DEFAULT_VIEW:
			m_model->setDefaultView();
		/*case Events::RESTART_WITH_NEW_PARTICLE_NUMBER:
				//std::cout << "model restart simulation\n";
			m_model->restart();*/
			break;
		default:
			break;
	}
}

void 		Controller::imGuiEventsAnalyses(Events const & ev)
{
	//std::cout << "Hello IMGui!!!\n";
	switch (ev) {
		case Events::PARTICLE_SYSTEM_CHANGE:
			m_model->setCurrentParticleSystem(static_cast<INIT_MESH>(m_view->getCurrentPs()));
            break;
        case Events::PARTICLES_NUMBERS_CHANGE:
			m_model->setCurrentParticleSystemNumbers(m_view->getParticleCount());
            break;
		case Events::START:
			std::cout << "model start simulation\n";
			m_model->start();
			break;
		case Events::STOP:
			std::cout << "model stop simulation\n";
			m_model->stop();
			break;
		case Events::RESTART_WITH_NEW_PARTICLE_NUMBER:
			//std::cout << "model restart simulation\n";
			m_model->restart();
			break;
		default:
			break;
	}
}
