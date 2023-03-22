#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	databaseFeed();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &ref)
{
	*this = ref;
}

BitcoinExchange::BitcoinExchange &operator=(BitcoinExchange const &ref)
{
	this->_btc = ref.getBtc();
}

BitcoinExchange::~BitcoinExchange(void)
{ }

std::map<std::string, std::string>	&BitcoinExchange::getBtc(void) const
{
	return (_btc);
}

void	BitcoinExchange::databaseFeed(void)
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
