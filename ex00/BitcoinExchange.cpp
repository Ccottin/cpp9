/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:21:38 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/23 16:47:01 by ccottin          ###   ########.fr       */
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

std::map<std::string, double>		BitcoinExchange::getBct(void) const
{
	return (_bct);
}

char								BitcoinExchange::check_date(std::string date) const
{
	size_t	i;
	size_t	y;
	int		check;

	i = date.find("-");
	if (i != 4 || date.find_first_not_of("0123456789") != i)
		return (1);
	y = i + 1;
	i = date.find("-", i + 1);
	check = std::atoi(date.substr(y, i).c_str());
	if (i - y != 2 || date.find_first_not_of("0123456789", y) != i || 
			check < 1 || check > 12)
		return (1);
	y = i + 1;
	date.find_first_not_of("0123456789", y);
	check = std::atoi(date.substr(y, date.size()).c_str());
	if ( date.size() - y != 2 || check < 1 || check > 31 ||
			date.find_first_not_of("0123456789", y) != std::string::npos)
		return (1);
	return (0);
}

void								BitcoinExchange::printResults(std::string line) const
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
	value = std::atof(line.substr(pipe + 3).c_str());
	if (value < 0)
		std::cout << "Error: not a positive number." << std::endl;
	else if (value > 1000)
		std::cout << "Error: too large a number." << std::endl;
	else
	{
		std::map<std::string, double>::const_iterator it = _bct.upper_bound(date);
		if (it != _bct.begin())
			it--;

	/*uncomment this ligne to show what line in database is used*/
	/*	std::cout << "    date = " << it->first
			<< "  quotient = " << it->second << std::endl;*/
		
		std::cout << date << " => " << value << " = " 
			<< it->second * value << std::endl;
	}
}

void								BitcoinExchange::database_feed(void)
{
	std::fstream	database;
	std::string		line;
	size_t			coma;

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

	while ( !(std::getline(database, line).eof()) )
	{
		coma = line.find(",");
		_bct[line.substr(0, coma)] = std::atof(line.substr(coma + 1, std::string::npos).c_str());
		line.clear();
	}
	database.close();
}
