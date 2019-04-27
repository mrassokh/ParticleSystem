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

# define LIVE_TIME 2.0f

#include <vector>

enum INIT_MESH
{
	S,
	C
};

typedef enum 	ParticleSystemType
{
	SPHERE,
  	CUBE
}				psType;

class Observer {
public:
	virtual void changeMesh(INIT_MESH mesh) = 0;
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
   	void notifyChangeMesh(INIT_MESH mesh);
private:
   	std::vector<Observer *> m_observers;
};



#endif /* end of include guard: MVC_BASE_HPP*/
