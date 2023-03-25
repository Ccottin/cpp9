/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:07:03 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/25 12:54:33 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int		check_digits(int ac, char **av)
{
	unsigned int	i;

	while (ac > 0)
	{
		i = 0;
		while (av[ac][i] && isdigit(av[ac][i]))
			++i;
		if (i != strlen(av[ac]))
			return (1);
		--ac;
	}
	return (0);
}

int		main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "Error : format." << std::endl;
		return (1);
	}
	if (check_digits(ac - 1, av))
	{
		std::cout << "Error : format." << std::endl;
		return (0);
	}

	PmergeMe	sort(ac - 1, av);
	
	sort.sortVector();
//	std::cout << "ac= " << ac << std::endl;
}

//gestion des overflow a faire
