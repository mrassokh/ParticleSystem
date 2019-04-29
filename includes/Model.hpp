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



typedef std::unique_ptr<ParticleManager> particleManager;
typedef std::unique_ptr<Camera> cameraPtr;

const float MOVE_SPEED       =  1.1f;
const float MOUSE_SENSITIVITY =  0.3f;

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
	particleManager 	m_particleManager;
	cameraPtr			m_camera;



};

#endif /* end of include guard:MODEL_HPP */
