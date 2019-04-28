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


#pragma #ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
public:
	Camera(glm::vec3 & pos, glm::vec3 & dir, float yaw, float pitch, float zoom);
	Camera(Camera const & rhs) = delete;
	Camera & operator = (Camera const & rhs) = delete;
	virtual ~Camera();

	glm::mat4 const & getView() const {return m_view;};
	glm::mat4 const & getProjection() const {return m_projection;};
private:
	float 		m_yaw;
    float 		m_pitch;
	float 		m_zoom;

	glm::vec3 	m_position;
    glm::vec3 	m_direction;
    glm::vec3 	m_up;
    glm::vec3 	m_right;
    glm::vec3 	m_commonUp;
    glm::mat4 	m_view;
	glm::mat4 	m_projection;


    /*float mMovementSpeed;
    float mMouseSensitivity;*/

};


#endif /* end of include guard: CAMERA_HPP */
