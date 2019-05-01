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
//   #include "View.hpp"
#include "Controller.hpp"

//void Hello();

int main()
{
	//Assimp::Importer importer;
	Model* model = new Model();
	//std::cout << "p1" << std::endl;
	//model.initModel();
	//std::cout << "p2" << std::endl;
	View *view = new View(model);
	model->initModel();
	Controller * controller = new Controller(model,view);
	controller->liveCycle();
	/*while (1){
		view->draw();
	}*/
	delete view;
	delete controller;
	printf("%s\n","end" );
    //std::cout << " Hello, WONDERFULL cmake world!!!" << std::endl;
    return 0;
}
