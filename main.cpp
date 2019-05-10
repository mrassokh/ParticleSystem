/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:59:19 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/13 11:59:21 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"
#include "Controller.hpp"



int main()
{

	Model* model = new Model();

	View *view = new View(model);
	model->initModel();
	Controller * controller = new Controller(model,view);
	controller->liveCycle();

	delete view;
	delete controller;

    return 0;
}
