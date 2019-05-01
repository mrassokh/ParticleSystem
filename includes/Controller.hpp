/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controller.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:31:10 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:31:12 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef  CONTROLLER_HPP
#define CONTROLLER_HPP
#include "Model.hpp"
#include "InputManager.hpp"


typedef std::unique_ptr<InputManager> ptrInput;
class Controller {
public:
	Controller (Model *model, View	*view);
	Controller(Controller & rhs) = delete;
	Controller & operator=(Controller & rhs) = delete;
	virtual ~Controller(){};

	void 			liveCycle();
	void 			eventsAnalyses(Events const & ev);
	void 			imGuiEventsAnalyses(Events const & ev);

private:
	Model 			*m_model;
	View			*m_view;
	ptrInput		m_inputManager;
};

#endif /* end of include guard: CONTROLLER_HPP */
