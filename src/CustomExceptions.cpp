/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomExceptions.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:35:07 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/31 17:35:09 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CustomExceptions.hpp"

CustomException::CustomException()
{
	m_Error = "Some strange error. God bless you!";
}

CustomException::CustomException(std::string Error)
{
	m_Error = Error;
}

CustomException::CustomException(const CustomException& rhs)
{
	m_Error = rhs.getError();
}

CustomException & CustomException::operator = (CustomException const & rhs)
{
	if (this != &rhs)
		m_Error = rhs.getError();
	return *this;
}

CustomException::~CustomException()
{

}

std::string 		CustomException::getError() const
{
	return m_Error;
}

const char* 		CustomException::what() const throw()
{
	return this->m_Error.c_str();
}
