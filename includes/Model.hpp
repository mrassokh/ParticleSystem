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

class Model : public Observable {
public:
	Model():m_mesh(SPHERE){};
	Model(Model const & rhs) = delete;
	Model & operator=(Model const & rhs) = delete;
	virtual ~Model(){};

	void 				setMesh(INIT_MESH mesh);
	const INIT_MESH 	getMesh() const {return m_mesh;};
private:
	INIT_MESH m_mesh;
};

#endif /* end of include guard:MODEL_HPP */
