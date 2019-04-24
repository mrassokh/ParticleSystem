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
    NOTHING,
    FINISH,
    FORWARD,
    BACKWARD,
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class InputManager {
public:
	InputManager(){};
	InputManager(InputManager const & rhs) = delete;
	InputManager operator = (InputManager const & rhs) = delete;
	~InputManager(){};

	Events eventProcessing(SDL_Event ev);
    /*Events KeyDownProcessin(SDL_Keycode keyPressed);
    Events processMouseMotion(SDL_Event const &ev);
    Events processMouseButton(SDL_MouseButtonEvent const &ev, bool isPressed);*/
//private:

};


#endif /* end of include guard: INPUT_MANAGER */
