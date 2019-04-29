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
#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"
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

	virtual void 	changeMesh(INIT_MESH mesh);
	void 			draw();
	const SDL_Event getEvent() const {return m_event;};
	const float 	getDeltaTime() const {return m_deltaTime;};
private:
	void 			initView();
	void 			initSDL();
	void 			initOpenGL();
	void 			initGui();

	void 			defineDeltaTime();


	INIT_MESH 		m_mesh;
	int           	m_width;
	int 			m_height;
    std::string   	m_head;
    SDL_Window   	*m_window;
    SDL_GLContext 	m_context;
    SDL_Event     	m_event;
	Model 			*m_model;
	glm::mat4 		m_projection;

	Uint64          m_curTime;
    Uint64          m_lastTime;
    float           m_deltaTime;
};
#endif /* end of include guard: VIEW_HPP */
