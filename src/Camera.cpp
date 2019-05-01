/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:34:36 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:34:39 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, float yaw, float pitch,
											float zoom) : m_position(pos),
														m_commonUp(glm::vec3(0.0f, 1.0f,  0.0f)),
														m_yaw(yaw),
														m_pitch(pitch),
														m_zoom(zoom),
														m_isCameraMove(false)
{
	calculateCameraVectors();
	findView();
	m_moveFunc.push_back(&Camera::moveRight);
	m_moveFunc.push_back(&Camera::moveLeft);
	m_moveFunc.push_back(&Camera::moveForward);
	m_moveFunc.push_back(&Camera::moveBackward);
}

Camera::~Camera()
{

}

void 		Camera::move(CameraChange ev,float const velocity)
{
	if (!m_isCameraMove)
		return;
	(this->*m_moveFunc[ev])(velocity);
	findView();
}

void 		Camera::calculateCameraVectors()
{
	calculateCameraDirection();
	calculateRightVector();
	calculateUpVector();
}

void 		Camera::calculateCameraDirection()
{
	glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_direction = glm::normalize(direction);
}

void 		Camera::rotate(float const deltaYaw,float const deltaPitch)
{
	if (!m_isCameraMove)
		return;
	m_yaw += deltaYaw;
	m_pitch += deltaPitch;
	if(m_pitch > 89.0f)
  		m_pitch =  89.0f;
	if(m_pitch < -89.0f)
  		m_pitch = -89.0f;
	calculateCameraVectors();
	findView();
}

void 		Camera::dropToDefaultCamera()
{
	m_position = glm::vec3(0.0f,0.0f,1.0f);
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	m_zoom = 90.0f;
	calculateCameraVectors();
	findView();
}
/*void 		Camera::moveRight(float velocity)
{
	m_position += m_right * velocity;
}

void 		Camera::moveLeft(float velocity)
{
	m_position += -m_right * velocity;
}

void 		Camera::moveForward(float velocity)
{
	m_position += m_direction * velocity;
}

void 		Camera::moveBackward(float velocity)
{
	m_position -= m_direction * velocity;
}*/

/*void 		Camera::rotateAroundY(float const velocity)
{

}
void 		Camera::rotateAroundX(float velocity)
{

}*/
