/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:07:00 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/24 22:28:14 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{ }

RPN::RPN(RPN const &ref)
{
	*this = ref;
}

RPN	&RPN::operator=(RPN const &ref)
{
	if (this != &ref)
	{
		_res = ref.getRes();
	}
	return (*this);
}

RPN::~RPN(void)
{ }

std::list<long int>	RPN::getRes(void) const
{
	return (_res);
}

void					RPN::calculate(char sign)
{
	long int	stock;
	

	stock = _res.back();
	_res.pop_back();
	if (sign == '*')
		_res.back() *= stock;
	else if (sign == '+')
		_res.back() += stock;
	else if (sign == '-')
		_res.back() -= stock;
	else if (sign == '/')	
		_res.back() /= stock;
}

void	RPN::print_elems(void)
{
	std::list<long int>::iterator	it = _res.begin();
	while (it != _res.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl; 
}

int		RPN::launch(std::string line)
{
	for (size_t i = 0; i < line.size(); ++i)
	{
		if (line[i] == ' ')
			continue ;
		else if (isdigit(line[i]))
			_res.push_back(line[i] - 48);
		else
		{
			if (_res.size() < 2 || (_res.back() == 0 && line[i] == '/'))
			{
				if (_res.back() == 0 && line[i] == '/')
					std::cout << "Questioning maths axioms :: ";
				return (1);
			}
			calculate(line[i]);
		}

		/*Uncomment this to have a digit per digit operation status*/
	/*	std::cout << "size = " << _res.size() << ", char = " << line[i] << std::endl;
		print_elems();*/
	}
	
	print_elems();
	return (0);
}
