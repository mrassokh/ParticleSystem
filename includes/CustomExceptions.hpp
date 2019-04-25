/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomExceptions.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:26:01 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/31 17:26:03 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_EXCEPTIONS
# define CUSTOM_EXCEPTIONS

#include <iostream>
#include <exception>

class CustomException : public std::exception
{
public:

    CustomException();
    CustomException(std::string Error);
    CustomException(const CustomException& rhs);
	CustomException & operator = (CustomException const & rhs);
    virtual ~CustomException();

    virtual const char* what() const throw();
	std::string 		getError() const;
private:
    std::string 		m_Error;
};
#endif
