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
        default:
            return Events::DEFAULT;
    }
}

Events InputManager::mouseMoveProcessing(SDL_Event const &ev)
{
	if (m_isMouseLeftButtomPressed)
    {
        m_mouseShift.x = ev.motion.x - m_prevXMouse;
        m_mouseShift.y = m_prevYMouse - ev.motion.y;

        m_prevXMouse = ev.motion.x;
        m_prevYMouse = ev.motion.y;
        return Events::ROTATE;
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
        default:
            break;
    }
}
