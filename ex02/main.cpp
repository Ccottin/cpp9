/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:07:03 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/23 20:58:45 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int		check_digits(int ac, char **av)
{
	int	i;

	while (ac > 1)
	{
		i = 0;
		if (isdigit(av[ac][i]) )
			i++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 1)
		return (0);
	check_digits(ac, av);
}
