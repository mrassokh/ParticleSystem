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

enum imGuiEvent {
	DEFAULT,
	PARTICLE_SYSTEM_CHANGE,
	PARTICLES_NUMBERS_CHANGE,
	START,
	STOP,
	RESTART_WITH_NEW_PARTICLE_NUMBER
};


class View : public Observer {
public:
	View(Model *model);
	View(View const & rhs) = delete;
	View & operator=(View const & rhs) = delete;
	virtual ~View();

	virtual void 		changeMesh(psType type);
	void 				draw();
	const SDL_Event 	getEvent() const {return m_event;};
	const imGuiEvent 	getImGuiEvent() const {return m_imGuiEvent;};
	const float 		getDeltaTime() const {return m_deltaTime;};
	const int			getWidth() const {return m_width;};
	const int			getHeight() const {return m_height;};
	const psType		getCurrentPs() const {return static_cast<psType>(m_imGuiInfo.ps);};
	const int 			getParticleCount() const {return m_imGuiInfo.particle_count;};
private:
	void 				drawPS(glm::mat4 const & projection);
	void 				drawPointPS(psPtr & particleSystem, glm::mat4 const & projection, glm::mat4  const & view, std::vector<glm::mat4> const & transforms);
	void 				initView();
	void 				initSDL();
	void 				initOpenGL();
	void 				initImGui();

	void 				defineDeltaTime();
	void 				drawImGui();
	void 				imGuiPollEvent();

	psType  			m_type;
	int           		m_width;
	int 				m_height;
    std::string   		m_head;
    SDL_Window   		*m_window;
    SDL_GLContext 		m_context;
    SDL_Event     		m_event;
	imGuiEvent 			m_imGuiEvent;
	imGuiInfo			m_imGuiInfo;
	Model 				*m_model;
	glm::mat4 			m_projection;

	Uint64          	m_curTime;
    Uint64          	m_lastTime;
	float           	m_deltaTime;
	float				m_FPS;
	float				m_FPS_inc;
	int					tick_counter;
	float				m_second;

	std::vector<void (View::*)(psPtr & particleSystem, glm::mat4 const & projection, glm::mat4  const & view,
		 						std::vector<glm::mat4> const & transforms)>	m_drawPs;

};
#endif /* end of include guard: VIEW_HPP */
