/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MVCBase.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:57:27 by mrassokh          #+#    #+#             */
/*   Updated: 2019/04/18 12:57:28 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MVCBase.hpp"


void Observable::addObserver(Observer * observer)
{
	m_observers.push_back(observer);
}

void Observable::notifyChangeMesh(psType type)
{
  for (auto &obs : m_observers) {
	 	obs->changeMesh(type);
  }
}
