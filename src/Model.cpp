/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:33:11 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:33:13 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Model.hpp"

Model::Model():m_mesh(S), m_isRunning(true)
{
	m_particleManager = std::make_unique<ParticleManager>();
}

void 		Model::setMesh(INIT_MESH mesh)
{
	m_mesh = mesh;
	notifyChangeMesh(mesh);
}

void 		Model::initModel()
{
	loadResources();
	initParticleSystems();

	/*GLfloat vertices[] = {
	    -0.5f, -0.5f, 0.0f,
	     0.5f, -0.5f, 0.0f,
	     0.0f,  0.5f, 0.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);*/
}

void 		Model::loadResources()
{
	try {
		RESOURCE.loadShader("../shaders/point.vx.glsl", "../shaders/point.ft.glsl", "point_shader");
		RESOURCE.addKernel("../kernels/init_sphere_by_points.cl","initSphere","initSphereProgram", "initSphereKernel","initialize_sphere");
		RESOURCE.addKernel("../kernels/update_sphere_by_points.cl","updateSphere","updateSphereProgram", "updateSphereKernel","update_sphere");
		RESOURCE.initParticleInfo(SPHERE,"initSphereKernel", "updateSphereKernel", "point_shader", "", LIVE_TIME);
	} catch (CustomException &ex) {
		std::cout << ex.what() << std::endl;
		exit(42);
	}
}

void 		Model::initParticleSystems()
{
	m_particleManager->init();
	//m_particleManager->startDrawPS(SPHERE);
}

void 		Model::draw()
{

	/*glm::mat4 groundModel = glm::mat4(1.0f);
	//std::vector<glm::mat4> transforms;
	//transforms.push_back(groundModel);
	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  0.0f);
	glm::vec3 cameraFront = glm::vec3(1.0f, 1.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection = glm::perspective(glm::radians(45.3f), static_cast<float>(800) / static_cast<float>(600), 0.1f, 10.0f);
	m_particleManager->draw(projection, view);*/
}
