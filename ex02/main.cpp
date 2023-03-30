/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:07:03 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/30 17:19:16 by ccottin          ###   ########.fr       */
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
		return (1);
	}

	PmergeMe	sort;
	
	sort.sortVector(ac, av);
	sort.sortDeque(ac, av);

	if (sort.getVSorted().size() == 0)
		return (1);

	sort.printResults(av, ac);
}
