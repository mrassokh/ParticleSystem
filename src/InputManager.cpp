/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:43:38 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/24 12:43:40 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputManager.hpp"

Events 	InputManager::eventProcessing(SDL_Event ev)
{
	if (ev.type == SDL_QUIT || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE))
		return Events::FINISH;
	ImGui_ImplSdlGL3_ProcessEvent(&ev);
	switch (ev.type)
	{
        case SDL_KEYDOWN:
            return keyProcessing(ev.key.keysym.sym);
        case SDL_MOUSEMOTION:
            return mouseMoveProcessing(ev);
        case SDL_MOUSEBUTTONDOWN:
            mouseButtonProcessing(ev.button, true);
            break;
        case SDL_MOUSEBUTTONUP:
            mouseButtonProcessing(ev.button, false);
            break;
        default:
            return Events::DEFAULT;
    }
    return Events::DEFAULT;
}


Events InputManager::keyProcessing(SDL_Keycode keyCode)
{
	switch (keyCode)
    {
        case SDLK_ESCAPE:
            return Events::FINISH;
        case SDLK_w:
            return Events::FORWARD;
        case SDLK_s:
            return Events::BACKWARD;
        case SDLK_a:
            return Events::LEFT;
        case SDLK_d:
            return Events::RIGHT;
		case SDLK_g:
			if (m_isGravityActive)
				m_isGravityActive = false;
			else m_isGravityActive = true;
			return m_isGravityActive ? Events::GRAVITY_ON : Events::GRAVITY_OFF;
		case SDLK_h:
			return Events::DROP_TO_DEFAULT_VIEW;
		case SDLK_f:
			return Events::CHANGE_CAMERA_MOVE_MODE;
		case SDLK_r:
			return Events::RESTART_WITH_NEW_PARTICLE_NUMBER;
        default:
            return Events::DEFAULT;
    }
}

Events InputManager::mouseMoveProcessing(SDL_Event const &ev)
{
	m_mouseShift.x = ev.motion.x - m_prevXMouse;
	m_mouseShift.y = m_prevYMouse - ev.motion.y;

	m_prevXMouse = ev.motion.x;
	m_prevYMouse = ev.motion.y;
	if (m_isMouseLeftButtomPressed) {
        return Events::ROTATE;
    } else if (m_isMouseRightButtomPressed && m_isGravityActive) {
		return Events::SET_GRAVITY_CENTER;
	}
    return Events::DEFAULT;
}

Events InputManager::mouseButtonProcessing(SDL_MouseButtonEvent const &ev, bool buttonPressed)
{
	switch (ev.button)
    {
        case SDL_BUTTON_RIGHT:
			if (!m_isMouseLeftButtomPressed) {
            	m_isMouseRightButtomPressed = buttonPressed;
            	m_prevXMouse = ev.x;
            	m_prevYMouse = ev.y;
				}
        break;
		case SDL_BUTTON_LEFT:
			if (!m_isMouseRightButtomPressed){
				m_isMouseLeftButtomPressed = buttonPressed;
				m_prevXMouse = ev.x;
				m_prevYMouse = ev.y;
			}
			break;
        default:
            break;
    }
	//return Events::DEFAULT;
}

Events 		InputManager::imGuiEventProcessing(imGuiEvent ev)
{
	switch (ev)
    {
		case imGuiEvent::PARTICLE_SYSTEM_CHANGE:
            return Events::PARTICLE_SYSTEM_CHANGE;
        case imGuiEvent::PARTICLES_NUMBERS_CHANGE:
            return Events::PARTICLES_NUMBERS_CHANGE;
		case imGuiEvent::START:
			std::cout << "Start event processed\n";
			return Events::START;
		case imGuiEvent::STOP:
			std::cout << "Stop event processed\n";
			return Events::STOP;
		case imGuiEvent::RESTART_WITH_NEW_PARTICLE_NUMBER:
			std::cout << "RESTART_WITH_NEW_PARTICLE_NUMBER event processed\n";
			return Events::RESTART_WITH_NEW_PARTICLE_NUMBER;
		default:
			return Events::DEFAULT;
	}
}
