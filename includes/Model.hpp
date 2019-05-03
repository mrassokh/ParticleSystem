/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:30:43 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:30:45 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_HPP
#define MODEL_HPP

#include "MVCBase.hpp"
#include "Resource.hpp"
#include "ParticleManager.hpp"
#include "GL/glew.h"
#include "Camera.hpp"


struct imGuiInfo {
	int 	 	ps;
	int 	 	prev_ps;
	int 		particle_count;
	int 		prev_particle_count;
};


typedef std::unique_ptr<ParticleManager> particleManager;
typedef std::unique_ptr<Camera> cameraPtr;

const float MOVE_SPEED       =  1.1f;
const float MOUSE_SENSITIVITY =  0.3f;
const float DISTANCE_FROM_CAMERA_TO_GRAVITY_PLANE =  1.0f;


class Model : public Observable {
public:
	Model();//:m_mesh(SPHERE), m_isRunning(true);
	Model(Model const & rhs) = delete;
	Model & operator=(Model const & rhs) = delete;
	virtual ~Model(){};

	void 				setMesh(INIT_MESH mesh);
	const INIT_MESH 	getMesh() const {return m_mesh;};
	const bool			getIsRunning() const {return m_isRunning;};

	void 				setIsRunning(bool isRunning) {m_isRunning = isRunning;};

	glm::mat4 const & 	getCameraView() {return m_camera->getView();};
	float 				getCameraZoom() {return m_camera->getZoom();};
	void 				cameraMoveRight(const float deltaTime) {m_camera->move(TO_RIGHT, deltaTime * MOVE_SPEED);};
	void 				cameraMoveLeft(const float deltaTime) {m_camera->move(TO_LEFT, deltaTime * MOVE_SPEED);};
	void 				cameraMoveBackward(const float deltaTime) {m_camera->move(TO_BACKWARD, deltaTime * MOVE_SPEED);};
	void 				cameraMoveForward(const float deltaTime) {m_camera->move(TO_FORWARD, deltaTime * MOVE_SPEED);};
	void 				cameraRotate(float deltaX, float deltaY){m_camera->rotate(deltaX * MOUSE_SENSITIVITY, deltaY * MOUSE_SENSITIVITY);};
	void 				initModel();
	void 				draw();

	void   				setIsGravityActive(bool isGravity) {m_isGravityActive = isGravity;};
	void   				setGravityCenter(int mouseX, int mouseY, int width, int height);// {m_isGravityActive = isGravity};
	void 				dropToDefaultGravityCenter();
	void   				setDefaultView();
	void 				start() {m_particleManager->startCurrentParticleSystem(m_mesh);};
	void 				stop() {m_particleManager->stopCurrentParticleSystem(m_mesh);};
	void 				restart();
	void 				setCurrentParticleSystem(INIT_MESH ps){m_mesh = ps;};
	void				setCurrentParticleSystemNumbers(int numbers) {m_currentParticleCount = numbers;};
	void 				changeIsCameraMoveMode(){m_camera->changeIsCameraMoveMode();};
	//int & 				getCurrentParticleSystemCount() {m_particleManager->getCurrentParticleSystemCount(m_mesh);};


	GLuint VBO;
	GLuint VAO;
	GLuint vertexShader;
	std::shared_ptr<Shader> m_shader;
	glm::mat4 view;
	glm::mat4 projection;
private:
	void 				loadResources();
	void 				initParticleSystems();

	INIT_MESH 			m_mesh;
	bool 				m_isRunning;
	bool 				m_isGravityActive;
	glm::vec3			m_gravityCenter;
	particleManager 	m_particleManager;
	cameraPtr			m_camera;
	int 				m_currentParticleCount;
};

#endif /* end of include guard:MODEL_HPP */
