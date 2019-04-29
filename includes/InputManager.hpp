/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:43:23 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/24 12:43:25 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  INPUT_MANAGER
#define INPUT_MANAGER
#include "SDL.h"

enum class Events
{
    DEFAULT,
    FINISH,
    FORWARD,
    BACKWARD,
    UP,
    DOWN,
    RIGHT,
    LEFT,
	ROTATE
};

struct mouseShiftCoord {
	int x;
	int y;
};

class InputManager {
public:
	InputManager(){};
	InputManager(InputManager const & rhs) = delete;
	InputManager operator = (InputManager const & rhs) = delete;
	~InputManager(){};

	mouseShiftCoord const & getMouseShiftCoord() const { return m_mouseShift;};
	Events eventProcessing(SDL_Event ev);

private:
	Events keyProcessing(SDL_Keycode keyPressed);
	Events mouseMoveProcessing(SDL_Event const &ev);
	Events mouseButtonProcessing(SDL_MouseButtonEvent const &ev, bool buttonPressed);

	bool 				m_isMouseRightButtomPressed;
	bool 				m_isMouseLeftButtomPressed;
	int 				m_prevXMouse;
	int 				m_prevYMouse;
	mouseShiftCoord		m_mouseShift;
};


#endif /* end of include guard: INPUT_MANAGER */
