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
#include "system.h"
#include "View.hpp"
#include "Controller.hpp"
//void Hello();

int main()
{
	//Assimp::Importer importer;
	Model model;
	View *view = new View(&model);
	Controller * controller = new Controller(&model,view);
	controller->liveCycle();
	/*while (1){
		view->draw();
	}*/
	delete view;
	delete controller;
    //std::cout << " Hello, WONDERFULL cmake world!!!" << std::endl;
    return 0;
}
