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



View::View(Model *model) : m_mesh(S), m_width(WIN_X), m_height(WIN_Y), m_head (""),m_model(model), m_second(0.0f)
{
	initView();
	m_model->addObserver(this);

}

View::~View()
{

}
void View::changeMesh(INIT_MESH mesh)
{
	m_mesh = mesh;
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
	m_imGuiInfo.ps = S;
	m_imGuiInfo.prev_ps = m_imGuiInfo.ps;
	m_imGuiInfo.particle_count = INIT_PARTICLE_COUNT;
	m_imGuiInfo.prev_particle_count = m_imGuiInfo.particle_count;
	m_imGuiEvent = imGuiEvent::DEFAULT;
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
    //ImGuiIO &io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    ImGui_ImplSdlGL3_Init(m_window);

    ImGui::StyleColorsDark();

    // io.Fonts->AddFontFromFileTTF("Assets/font/Roboto-Medium.ttf", 16.0f);

}
void 		View::drawImGui()
{
	ImGui_ImplSdlGL3_NewFrame(m_window);
	std::cout<<"DRAW IM GUI!!!\n\n\n";
		//ImGui::SetNextWindowSize(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::SetNextWindowPos({0, 0},0);
			ImGui::SetNextWindowBgAlpha(0.7f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10,10));
			//if (ImGui::BeginMenuBar()){
			//	ImGui::RadioButton("SPHERE", &m_imGuiInfo.ps, S);

			//if(ImGui::Begin("Menu"))//{
				ImGui::Begin("Menu");
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
			//ImGui::Text("Welcome to BomberMan game!");
			//ImGui::SliderInt("particles number", &m_model->getCurrentParticleSystemCount(), 100000, 3000000);
			ImGui::Text("FPS: %f", m_FPS);
			ImGui::Text("Particles number!");
			ImGui::SliderInt("", &m_imGuiInfo.particle_count, 100000, 3000000);

			ImGui::RadioButton("SPHERE", &m_imGuiInfo.ps, S);
			ImGui::RadioButton("CUBE", &m_imGuiInfo.ps, C);
			/////////////////////////////////HARDNESS////////////////////////////////////

			//ImGui::Separator();

			//ShowHardnessRadioButtons();

			/////////////////////////////////START GAME////////////////////////////////////

			//ImGui::Separator();

			//const ImVec2 menu_frame = {200, 120};
			//const float spacing = 10;
			//ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, spacing));
			//ImGui::BeginChildFrame(1, menu_frame, 4);

			//ShowStartNewGameMenu();

			/////////////////////////////////LOAD GAME////////////////////////////////////

			//ShowLoadSavedGamesMenu();

			/////////////////////////////////EXIT////////////////////////////////////

			//ImGui::Button("START", STANDARD_MENU_BUTTON);

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

//ImGui::Text("MovableEntity setting:");
			//ImGui::EndChildFrame();
			//ImGui::PopStyleVar();
			ImGui::PopStyleVar();
			ImGui::End();
		//}

		/*	ImGui::EndMenuBar();
	}*/
			ImGui::PopStyleVar();

		ImGui::Render();
	    ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
}
void 		View::draw()
{
	defineDeltaTime();

	//std::cout << "View deltatime is " << m_deltaTime;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glViewport(0, 0, m_width, m_height);
	 m_projection = glm::perspective(glm::radians(m_model->getCameraZoom()), static_cast<float>(m_width) / static_cast<float>(m_height), 0.1f, 100.0f);
	 m_model->draw();
	 m_model->m_shader->use();
	 m_model->m_shader->setMat4("view", m_model->getCameraView());
	//m_model->m_shader->setMat4("view", m_model->view);
 	m_model->m_shader->setMat4("projection", m_projection);
	glBindVertexArray(m_model->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	imGuiPollEvent();
	drawImGui();

	SDL_PollEvent(&m_event);

	SDL_GL_SwapWindow(m_window);
}

void 		View::defineDeltaTime()
{
	m_lastTime = m_curTime;
	m_curTime = SDL_GetPerformanceCounter();
	m_deltaTime = (m_curTime - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

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
