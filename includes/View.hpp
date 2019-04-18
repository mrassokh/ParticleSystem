/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   View.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:31:24 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:31:25 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  VIEW_HPP
#define VIEW_HPP

#include "MVCBase.hpp"
#include "Model.hpp"
#include "SDL.h"
#include <imgui.h>
#include "GL/glew.h"
#include "cl.hpp"
#define  WIN_X  800
#define  WIN_Y  600
#define  WIN_SIZE {WIN_X, WIN_Y}

class View : public Observer {
public:
	//View();
	View(Model *model);
	View(View const & rhs) = delete;
	View & operator=(View const & rhs) = delete;
	virtual ~View();

	virtual void changeMesh(INIT_MESH mesh);
private:
	void 			initView();
	void 			initSDL();
	void 			initOpenGL();
	void 			draw();

	INIT_MESH 		m_mesh;
	int           	m_width;
	int 			m_height;
    std::string   	m_head;
    SDL_Window   	*m_window;
    SDL_GLContext 	m_context;
    SDL_Event     	m_event;
	Model 			*m_model;
};
#endif /* end of include guard: VIEW_HPP */
