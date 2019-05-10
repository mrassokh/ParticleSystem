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

Model::Model():m_type(SPHERE), m_isRunning(true),m_isGravityActive(false),
 				m_gravityCenter(glm::vec3(0.0f,0.0f,0.0f)), m_currentParticleCount(INIT_PARTICLE_COUNT)
{
	glm::vec3 pos = glm::vec3(0.0f,0.0f,1.0f);
	m_camera = std::make_unique<Camera>(pos, -90.0f, 0.0f, 90.0f);
}

void 		Model::setMesh(psType const type)
{
	m_type = type;
	notifyChangeMesh(type);
}

void 		Model::initModel()
{
	loadResources();
	m_particleManager = std::make_unique<ParticleManager>();
	initParticleSystems();
}

void 		Model::loadResources()
{
	try {
		RESOURCE.loadShader("../shaders/point.vx.glsl", "../shaders/point.ft.glsl", "point_shader");
		RESOURCE.loadShader("../shaders/point_time.vx.glsl", "../shaders/point_time.ft.glsl", "point_time_shader");

		RESOURCE.addKernel("../kernels/init_sphere_by_points.cl","initSphere","initSphereProgram", "initSphereKernel","initialize_sphere");

		RESOURCE.addKernel("../kernels/update_sphere_by_points.cl","updateSphere","updateSphereProgram", "updateSphereKernel","update_sphere");
		RESOURCE.initParticleInfo(SPHERE,"initSphereKernel", "updateSphereKernel", "point_shader", "", LIVE_TIME);

		RESOURCE.addKernel("../kernels/init_cube_by_points.cl","initCube","initCubeProgram", "initCubeKernel","initialize_Cube");
		RESOURCE.addKernel("../kernels/update_cube_by_points.cl","updateCube","updateCubeProgram", "updateCubeKernel","update_Cube");

		RESOURCE.initParticleInfo(CUBE,"initCubeKernel", "updateCubeKernel", "point_shader", "", LIVE_TIME);
		RESOURCE.addKernel("../kernels/update_cube_by_points_liveTime.cl","updateCubeLiveTime","updateCubeProgramLiveTime", "updateCubeKernelLiveTime","update_Cube");
		RESOURCE.initParticleInfo(CUBE_EXPLOSION,"initCubeKernel", "updateCubeKernelLiveTime", "point_time_shader", "", LIVE_TIME);

		RESOURCE.addKernel("../kernels/update_sphere_by_points_liveTime.cl","updateSphereLiveTime","updateSphereProgramLiveTime", "updateSphereKernelLiveTime","update_sphere");
		RESOURCE.initParticleInfo(SPHERE_EXPLOSION,"initSphereKernel", "updateSphereKernelLiveTime", "point_time_shader", "", LIVE_TIME);
	} catch (CustomException &ex) {
		std::cout << ex.what() << std::endl;
		exit(42);
	}
}

void 		Model::initParticleSystems()
{
	m_particleManager->init();
}

void   			Model::setPointFromMouse(int mouseX, int mouseY, int width, int height, bool isGravityPoint)
{
	int centeredX = mouseX - width / 2;
	int centeredY = -(mouseY - height / 2);
	float rightDistance = static_cast<float> (centeredX * 2) / static_cast<float>(width);
	float upDistance = static_cast<float> (centeredY * 2) / static_cast<float>(height);
	glm::vec3 rightVector = m_camera->getRight() *  rightDistance;
	glm::vec3 upVector = m_camera->getUp() *  upDistance;
	glm::vec3 forwardVector = m_camera->getDirection() * DISTANCE_FROM_CAMERA_TO_GRAVITY_PLANE;
	if (isGravityPoint) {
		m_gravityCenter = m_camera->getPosition() + forwardVector + rightVector + upVector;
	} else {
		m_cursorPoint = m_camera->getPosition() + forwardVector + rightVector + upVector;
	}
}

inline void   			Model::dropToDefaultGravityCenter()
{
	m_gravityCenter = glm::vec3(0.0f,0.0f,0.0f);
}

void   			Model::setDefaultView()
{
	dropToDefaultGravityCenter();
	m_camera->dropToDefaultCamera();
}
