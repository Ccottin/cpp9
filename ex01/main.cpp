/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:51:01 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/23 18:14:57 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	ReversePolishNotation(char *av)
{
	std::string	line(av);
	
	if (line.find_first_not_of("0123456789+-/* ") != std::string::npos)
		return (1);

	RPN	data;

	return (data.launch(line));
}

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Unvalid format." << std::endl;
		return (1);
	}
	if (ReversePolishNotation(av[1]))
	{
		std::cout << "Error." << std::endl;
		return (1);
	}
	return (0);
}
