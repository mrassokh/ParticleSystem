/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MVCBase.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:45:29 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:45:31 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MVC_BASE_HPP
#define MVC_BASE_HPP
#include <vector>

typedef enum 	ParticleSystemType
{
	SPHERE,
  	CUBE,
	SPHERE_EXPLOSION,
	CUBE_EXPLOSION
}				psType;

class Observer {
public:
	virtual void changeMesh(psType type) = 0;
};

typedef std::shared_ptr<Observer> viewPtr;

class Observable
{

public:
	Observable() {};
	Observable(Observable const & rhs) = delete;
	Observable & operator=(Observable const & rhs) = delete;
	virtual ~Observable() {m_observers.clear();};

	void addObserver(Observer *observer);
   	void notifyChangeMesh(psType type);
private:
   	std::vector<Observer *> m_observers;
};



#endif /* end of include guard: MVC_BASE_HPP*/
