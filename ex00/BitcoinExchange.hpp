#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <stdlib.h>

class	BitcoinExchange
{
	public :

		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &ref);
		BitcoinExchange &operator=(BitcoinExchange const &ref);
		~BitcoinExchange(void);


		std::map<std::string, std::string>	&getBtc(void) const;
		

	private :

		void	databaseFeed(void);
		
		std::map<std::string, std::string>	_bct;
}

#endif
