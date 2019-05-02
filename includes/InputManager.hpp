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
#include "View.hpp"
#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"

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
	ROTATE,
	CHANGE_CAMERA_MOVE_MODE,
	GRAVITY_ON,
	GRAVITY_OFF,
	SET_GRAVITY_CENTER,
	DROP_TO_DEFAULT_VIEW,
	PARTICLE_SYSTEM_CHANGE,
	PARTICLES_NUMBERS_CHANGE,
	START,
	STOP,
	RESTART_WITH_NEW_PARTICLE_NUMBER
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

	mouseShiftCoord const & getMouseShiftCoord() const {return m_mouseShift;};
	Events 					eventProcessing(SDL_Event ev);
	Events 					imGuiEventProcessing(imGuiEvent ev);
	int const				getXMouse() const {return m_prevXMouse;};
	int const				getYMouse() const {return m_prevYMouse;};
private:
	Events keyProcessing(SDL_Keycode keyPressed);
	Events mouseMoveProcessing(SDL_Event const &ev);
	Events mouseButtonProcessing(SDL_MouseButtonEvent const &ev, bool buttonPressed);

	bool 				m_isMouseRightButtomPressed;
	bool 				m_isMouseLeftButtomPressed;
	bool				m_isGravityActive;
	int 				m_prevXMouse;
	int 				m_prevYMouse;
	mouseShiftCoord		m_mouseShift;
};


#endif /* end of include guard: INPUT_MANAGER */
