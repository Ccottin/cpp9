/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:21:47 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/23 16:41:23 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <stdlib.h>

class	BitcoinExchange
{
	public :

		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &ref);
		BitcoinExchange &operator=(BitcoinExchange const &ref);
		~BitcoinExchange(void);

		std::map<std::string, double>		getBct(void) const;
		void								printResults(std::string line) const;
		
	private :

		void	database_feed(void);
		char	check_date(std::string date) const;
		std::map<std::string, double>	_bct;
};

#endif
