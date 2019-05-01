/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:32:05 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:32:06 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraChange
{
	TO_RIGHT,
	TO_LEFT,
	TO_BACKWARD,
	TO_FORWARD
};


class Camera {
public:
	Camera(glm::vec3 pos, float yaw, float pitch, float zoom);
	Camera(Camera const & rhs) = delete;
	Camera & operator = (Camera const & rhs) = delete;
	virtual ~Camera();

	glm::mat4 const & 	getView() const {return m_view;};
	glm::vec3 const & 	getDirection() const {return m_direction;};
	glm::vec3 const & 	getRight() const {return m_right;};
	glm::vec3 const & 	getUp() const {return m_up;};
	glm::vec3 const & 	getPosition() const {return m_position;};
	float 				getZoom() const {return m_zoom;};
	void 				move(CameraChange ev,float const velocity);
	void 				rotate(float const deltaYaw,float const deltaPitch);
	void 				dropToDefaultCamera();
	void 				changeIsCameraMoveMode() {m_isCameraMove = !m_isCameraMove;};
private:
	void 				calculateCameraVectors();
	void 				calculateCameraDirection();
	void 				calculateRightVector() {m_right = glm::normalize(glm::cross(m_direction, m_commonUp));};
	void 				calculateUpVector() {m_up = glm::normalize(glm::cross(m_right, m_direction));};
	void 				findView() {m_view = glm::lookAt(m_position, m_position + m_direction, m_up);};
	void 				moveRight(float const velocity) {m_position += m_right * velocity; std::cout << "right" << velocity<<  std::endl;};
	void 				moveLeft(float const velocity) {m_position += -m_right * velocity;};
	void 				moveForward(float const velocity){m_position -= m_direction * velocity;};
	void 				moveBackward(float const velocity){m_position += m_direction * velocity;};


	//void 		rotateAroundY(float velocity);
	//void 		rotateAroundX(float velocity);
	//void 		findProjection() {m_projection = glm::perspective(glm::radians(m_zoom), static_cast<float>(mWidth) / static_cast<float>(mHeight), 2.1f, 90.0f);};

	glm::vec3 	m_position;
    glm::vec3 	m_direction;
    glm::vec3 	m_up;
    glm::vec3 	m_right;
    glm::vec3 	m_commonUp;
    glm::mat4 	m_view;
	//glm::mat4 	m_projection;

	float 		m_yaw;
    float 		m_pitch;
	float 		m_zoom;

	bool 		m_isCameraMove;
	std::vector<void (Camera::*)(float const velocity)>      	m_moveFunc;


    /*float mMovementSpeed;
    float mMouseSensitivity;*/

};


#endif /* end of include guard: CAMERA_HPP */
