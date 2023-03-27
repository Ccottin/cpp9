/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:07:03 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/27 17:20:42 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int		check_digits(int ac, char **av)
{
	unsigned int	i;
	int				tmp; //HEREE PLUS MODIF
	std::set<unsigned>	check;

	tmp = ac;
	while (ac > 0)
	{
		i = 0;
		while (av[ac][i] && isdigit(av[ac][i]))
			++i;
		if (i != strlen(av[ac]))
			return (1);
		--ac;
	}

	while (tmp > 0)
	{
		if (check.insert(atoi(av[tmp])).second == false)
		{
			std::cout << "found a double!" << std::endl;
			return (1);
		}
		--tmp;
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
		return (1);
	}

	PmergeMe	sort(ac - 1, av);
	
	sort.sortVector();
	sort.sortDeque();
	std::cout << " ac = " << ac - 1 << std::endl << std::endl;


	sort.printResults(av, ac);
}

//gestion des overflow a faire
