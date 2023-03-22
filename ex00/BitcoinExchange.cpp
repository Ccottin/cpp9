/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:21:38 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/22 20:45:41 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	database_feed();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &ref)
{
	*this = ref;
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &ref)
{
	if (this != &ref)
		this->_bct = ref.getBct();
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{ }

std::map<std::string, std::string>		BitcoinExchange::getBct(void) const
{
	return (_bct);
}

char	BitcoinExchange::check_date(std::string date) const
{
	/*still need to invalidate or no if wrong month of the year*/
	size_t	i;
	size_t	y;

	i = date.find("-");
	if (i != 4 || date.find_first_not_of("0123456789") != i)
		return (1);
	y = i;
	i = date.find("-", i + 1);
	if ((i - y != 1 && i - y != 2) || date.find_first_not_of("0123456789") != i)
		return (1);
	y = i;
	i = date.find("-", i + 1);
	if ((i - y != 1 && i - y != 2) || date.find_first_not_of("0123456789") != i)
		return (1);
	return (0);
}

void	BitcoinExchange::printResults(std::string line) const
{
	size_t			pipe;
	double			value;
	std::string		date;

	pipe = line.find(" | ");
	if (pipe == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}
	date = line.substr(0, pipe);
	if (check_date(date))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}
	value = std::atof(line.substr(pipe + 4).c_str());
	if (value < 0)
		std::cout << "Error: not a positive number." << std::endl;
	else if (value < 0)
		std::cout << "Error: too large a number." << std::endl;
	else
	{
		std::map<std::string, std::string>::const_iterator it = _bct.upper_bound(date);
		it--;
		std::cout << date << " => " << value << " = " << std::atof(it->second.c_str()) * value;
	}
}

void	BitcoinExchange::database_feed(void)
{
	std::fstream						database;
	std::string							line;
	size_t								coma;

	database.open("data.csv", std::fstream::in );
	if (!database.is_open())
	{
		std::cerr << "Error: could not load database file." << std::endl;
		database.close();
		exit(1);
	}

	/*delete first line wich is format type*/
	std::getline(database, line);
	line.clear();
	coma = line.find(",");

	while ( !(std::getline(database, line).eof()) )
	{
		_bct[line.substr(0, coma)] = line.substr(coma + 1);
		line.clear();
	}
	database.close();
}
