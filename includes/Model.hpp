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
	int	 		ps;
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
	Model();
	Model(Model const & rhs) = delete;
	Model & operator=(Model const & rhs) = delete;
	virtual ~Model(){};

	void 				setMesh(psType const type);
	const psType 		getMesh() const {return m_type;};
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

	void   				setIsGravityActive(bool isGravity) {m_isGravityActive = isGravity;};
	void   				setGravityCenter(int mouseX, int mouseY, int width, int height);
	void 				dropToDefaultGravityCenter();
	void   				setDefaultView();

	void 				update() {m_particleManager->updateCurrentParticleSystem(m_type);};
	void 				start() {m_particleManager->startCurrentParticleSystem(m_type);};
	void 				stop() {m_particleManager->stopCurrentParticleSystem(m_type);};
	void 				reinit(){m_particleManager->reinitCurrentParticleSystem(m_type, m_currentParticleCount);};
	void 				setCurrentParticleSystem(psType const type){m_type = type;};
	void				setCurrentParticleSystemNumbers(int numbers) {m_currentParticleCount = numbers;};
	void 				changeIsCameraMoveMode(){m_camera->changeIsCameraMoveMode();};

	psPtr &				getCurrentParticleSystem() {return m_particleManager->getCurrentParticleSystem(m_type);};

private:
	void 				loadResources();
	void 				initParticleSystems();

	psType 				m_type;
	bool 				m_isRunning;
	bool 				m_isGravityActive;
	glm::vec3			m_gravityCenter;
	particleManager 	m_particleManager;
	cameraPtr			m_camera;
	int 				m_currentParticleCount;
};

#endif /* end of include guard:MODEL_HPP */
