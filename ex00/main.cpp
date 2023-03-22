/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:21:45 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/22 20:17:48 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	BitcoinExchangeLauncher(char *av)
{
	BitcoinExchange	data;
	std::fstream	database;
	std::string		line;
	
	database.open(av, std::fstream::in | std::fstream::out);
	if (!database.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		database.close();
		exit(1);
	}
	
	while ( !(std::getline(database, line).eof()) )
	{
		if (line.compare("date | value"))
			continue ;
		data.printResults(line);
		line.clear();
	}
	database.close();
}

int		main(int ac, char **av)
{
	switch (ac)
	{
		case 1 :
			std::cerr << "Error: could not open file." << std::endl;
			return (1);
		case 2 :
			BitcoinExchangeLauncher(av[1]);
			break ;
		default :
			std::cerr << "Wrong number of arguments." << std::endl;
			return (1);
	}
	return (0);
}
