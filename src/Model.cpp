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

Model::Model():m_mesh(S), m_isRunning(true),m_isGravityActive(false), m_gravityCenter(glm::vec3(0.0f,0.0f,0.0f)),
m_currentParticleCount(3)//m_currentParticleCount(INIT_PARTICLE_COUNT)
{
	//sm_particleManager = std::make_unique<ParticleManager>();

	glm::vec3 pos = glm::vec3(0.0f,0.0f,1.0f);
	m_camera = std::make_unique<Camera>(pos, -90.0f, 0.0f, 90.0f);
}

void 		Model::setMesh(INIT_MESH mesh)
{
	m_mesh = mesh;
	notifyChangeMesh(mesh);
}

void 		Model::initModel()
{
	loadResources();
	m_particleManager = std::make_unique<ParticleManager>();
	initParticleSystems();
	float x = 0;//m_gravityCenter.x;
	float y = 0;//m_gravityCenter.y;
	float z = 0;//m_gravityCenter.z;


	GLfloat vertices[] = {
	    -0.5f + x, -0.5f + y, 0.0f + z,
	     0.5f + x, -0.5f + y, 0.0f + z,
	     0.0f + x,  0.5f + y, 0.0f + z
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);

glBindVertexArray(0);

}

void 		Model::loadResources()
{
	try {
		RESOURCE.loadShader("../shaders/point.vx.glsl", "../shaders/point.ft.glsl", "point_shader");
		std::cout<< "p1\n";
		RESOURCE.addKernel("../kernels/init_sphere_by_points.cl","initSphere","initSphereProgram", "initSphereKernel","initialize_sphere");
std::cout<< "p2\n";
		RESOURCE.addKernel("../kernels/update_sphere_by_points.cl","updateSphere","updateSphereProgram", "updateSphereKernel","update_sphere");
		RESOURCE.initParticleInfo(SPHERE,"initSphereKernel", "updateSphereKernel", "point_shader", "", LIVE_TIME);

		RESOURCE.addKernel("../kernels/init_cube_by_points.cl","initCube","initCubeProgram", "initCubeKernel","initialize_Cube");
		RESOURCE.addKernel("../kernels/update_cube_by_points.cl","updateCube","updateCubeProgram", "updateCubeKernel","update_Cube");
		RESOURCE.initParticleInfo(CUBE,"initCubeKernel", "updateCubeKernel", "point_shader", "", LIVE_TIME);
	} catch (CustomException &ex) {
		std::cout << ex.what() << std::endl;
		exit(42);
	}
	m_shader = RESOURCE.getShader("point_shader");
}

void 		Model::initParticleSystems()
{
	m_particleManager->init();
	//m_particleManager->startDrawPS(SPHERE);
}

void 		Model::draw()
{
	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 pointTo = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
	//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	view = glm::lookAt(cameraPos, pointTo, cameraUp);
	projection = glm::perspective(glm::radians(getCameraZoom()), static_cast<float>(80) / static_cast<float>(60), 0.1f, 100.0f);
	/*m_shader->use();
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);*/

	//glm::mat4 groundModel = glm::mat4(1.0f);
	//std::vector<glm::mat4> transforms;
	//transforms.push_back(groundModel);
	/*glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  0.0f);
	glm::vec3 cameraFront = glm::vec3(1.0f, 1.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection = glm::perspective(glm::radians(45.3f), static_cast<float>(800) / static_cast<float>(600), 0.1f, 10.0f);*/
	m_particleManager->draw(projection, this->getCameraView());
}

void   			Model::setGravityCenter(int mouseX, int mouseY, int width, int height)
{
	int centeredX = mouseX - width / 2;
	int centeredY = -(mouseY - height / 2);
	float rightDistance = static_cast<float> (centeredX * 2) / static_cast<float>(width);
	float upDistance = static_cast<float> (centeredY * 2) / static_cast<float>(height);
	glm::vec3 rightVector = m_camera->getRight() *  rightDistance;
	glm::vec3 upVector = m_camera->getUp() *  upDistance;
	glm::vec3 forwardVector = m_camera->getDirection() * DISTANCE_FROM_CAMERA_TO_GRAVITY_PLANE;
	m_gravityCenter = m_camera->getPosition() + forwardVector + rightVector + upVector;

	std::cout << m_gravityCenter.x << " " << m_gravityCenter.y << " " << m_gravityCenter.z << std::endl;
}

void   			Model::dropToDefaultGravityCenter()
{
	m_gravityCenter = glm::vec3(0.0f,0.0f,0.0f);
	std::cout << m_gravityCenter.x << " " << m_gravityCenter.y << " " << m_gravityCenter.z << std::endl;
}

void   			Model::setDefaultView()
{
	dropToDefaultGravityCenter();
	m_camera->dropToDefaultCamera();
}

void 			Model::restart()
{
	m_particleManager->reinitCurrentParticleSystem(m_mesh, m_currentParticleCount);
	m_particleManager->startCurrentParticleSystem(m_mesh);
}
/*void 		Model::cameraRotate(const float deltaTime, float deltaX, float deltaY)
{

}*/
