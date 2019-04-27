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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
typedef std::unique_ptr<ParticleManager> particleManager;

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
	void 				initModel();
	void 				draw();
private:
	void 				loadResources();
	void 				initParticleSystems();

	INIT_MESH 			m_mesh;
	bool 				m_isRunning;
	particleManager 	m_particleManager;

	GLuint VBO;
	GLuint vertexShader;

};

#endif /* end of include guard:MODEL_HPP */
