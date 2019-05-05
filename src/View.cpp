/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   View.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:34:59 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:35:01 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "View.hpp"
#define  STANDARD_MENU_BUTTON {200, 30}



View::View(Model *model) : m_type(SPHERE), m_width(WIN_X), m_height(WIN_Y), m_head (""),m_model(model), m_second(0.0f)
{
	initView();
	m_model->addObserver(this);

}

View::~View()
{

}
void View::changeMesh(psType type)
{
	m_type = type;
}


void 		View::initView()
{
	initSDL();

	m_window = SDL_CreateWindow(m_head.c_str(), SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);
	SDL_GL_MakeCurrent(m_window, m_context);
	SDL_SetWindowResizable(m_window, SDL_TRUE);
	initImGui();
	initOpenGL();
	m_imGuiInfo.ps = SPHERE;
	m_imGuiInfo.prev_ps = m_imGuiInfo.ps;
	m_imGuiInfo.particle_count = INIT_PARTICLE_COUNT;
	m_imGuiInfo.prev_particle_count = m_imGuiInfo.particle_count;
	m_imGuiEvent = imGuiEvent::DEFAULT;
	m_drawPs.push_back(&View::drawPointPS);
	m_drawPs.push_back(&View::drawPointPS);
}

void 		View::initSDL()
{
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);

    int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);


    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void 		View::initOpenGL()
{
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("Aaaaaaaaaaa!");
		exit(0);
	}
	glViewport(0, 0, m_width, m_height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

void 	View::initImGui() {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSdlGL3_Init(m_window);
    ImGui::StyleColorsDark();
}
void 		View::drawImGui()
{
	ImGui_ImplSdlGL3_NewFrame(m_window);
	ImGui::SetNextWindowPos({0, 0},0);
	ImGui::SetNextWindowBgAlpha(0.7f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10,10));
	ImGui::Begin("Menu");
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
	ImGui::Text("FPS: %f", m_FPS);
	ImGui::Text("Particles number!");
	ImGui::SliderInt("", &m_imGuiInfo.particle_count, 100000, 3000000);
	ImGui::RadioButton("SPHERE", &m_imGuiInfo.ps, SPHERE);
	ImGui::RadioButton("CUBE", &m_imGuiInfo.ps, CUBE);
	if (ImGui::Button("START", STANDARD_MENU_BUTTON))
	{
		m_imGuiEvent = imGuiEvent::START;
	}
	if (ImGui::Button("STOP", STANDARD_MENU_BUTTON))
	{
		m_imGuiEvent = imGuiEvent::STOP;
	}
	if (ImGui::Button("RESTART", STANDARD_MENU_BUTTON))
	{
		m_imGuiEvent = imGuiEvent::RESTART_WITH_NEW_PARTICLE_NUMBER;
	}
	ImGui::PopStyleVar();
	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::Render();
    ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
}
void 		View::draw()
{
	defineDeltaTime();
	glClearColor(0.02f, 0.03f, 0.03f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_width, m_height);

	m_projection = glm::perspective(glm::radians(m_model->getCameraZoom()), static_cast<float>(m_width) / static_cast<float>(m_height), 0.1f, 100.0f);
 	drawPS(m_projection, m_model->getCursorPoint());
	imGuiPollEvent();
	drawImGui();

	SDL_PollEvent(&m_event);
	SDL_GL_SwapWindow(m_window);
}

void 		View::drawPS(glm::mat4 const & projection, glm::vec3 const & cursorPoint)
{
	std::vector<glm::mat4> transforms;
	glm::mat4 model = glm::mat4(1.0f);
	transforms.push_back(model);
	glm::mat4 projection_view = projection * m_model->getCameraView();
	(this->*m_drawPs[m_type])(m_model->getCurrentParticleSystem(),projection_view, cursorPoint, transforms);
}

void 		View::defineDeltaTime()
{
	m_lastTime = m_curTime;
	m_curTime = SDL_GetPerformanceCounter();
	m_deltaTime = (m_curTime - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

	//m_FPS = 1 / m_deltaTime;
	if (m_second < 1.0f){
		m_second += m_deltaTime;
		m_FPS_inc += 1 / m_deltaTime;
		//m_FPS_sum  += m_FPS;
		tick_counter++;
	} else {
		m_FPS = m_FPS_inc / tick_counter;
		m_FPS_inc = 0.0f;
		tick_counter = 0;
		m_second = 0.0f;
	}
}

void 		View::imGuiPollEvent()
{
	m_imGuiEvent = imGuiEvent::DEFAULT;
	if (m_imGuiInfo.ps != m_imGuiInfo.prev_ps) {
		m_imGuiInfo.prev_ps = m_imGuiInfo.ps;
		m_imGuiEvent = imGuiEvent::PARTICLE_SYSTEM_CHANGE;
		return;
	}
	if (m_imGuiInfo.particle_count != m_imGuiInfo.prev_particle_count) {
		m_imGuiInfo.prev_particle_count = m_imGuiInfo.particle_count;
		m_imGuiEvent = imGuiEvent::PARTICLES_NUMBERS_CHANGE;
		return;
	}
}

//void 		View::drawPointPS(psPtr & particleSystem, glm::mat4 const & projection, glm::mat4  const & view, std::vector<glm::mat4> const & transforms)
void 		View::drawPointPS(psPtr & particleSystem, glm::mat4 const & projection_view, glm::vec3 const & cursorPoint, std::vector<glm::mat4> const & transforms)
{
	auto shader = particleSystem->getShader();
	if (!shader)
		throw CustomException("Shader for particle system is not defined!");

	shader->use();
	shader->setMat4("projection_view", projection_view);
	shader->setVec3("cursorPoint", cursorPoint);
	//shader->setMat4("projection", projection);
	//shader->setMat4("view", view);
	//std::cout << "drawGLContent \n ";
	//	printf("drawGLContent \n");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindBuffer(GL_ARRAY_BUFFER, particleSystem->getIBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * transforms.size(), &transforms[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(particleSystem->getVAO());
	glDrawArraysInstanced(GL_POINTS, 0, particleSystem->getParticleCount(), transforms.size());
	//glDrawArrays(GL_POINTS, 0, particleSystem->getParticleCount());
	glBindVertexArray(0);
	glDisable(GL_BLEND);
	glFinish();
}
