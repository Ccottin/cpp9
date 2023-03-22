#include "BitcoinExchange.hpp"

void	BitcoinExchangeLauncher(char *av)
{
	std::fstream						database;
	std::string							line;
	
	database.open(av, std::fstream::in | std::fstream::out);
	if (!database.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		database.close();
		exit(1);
	}

	BitcoinExchange	data;

	data.setList(database);
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
