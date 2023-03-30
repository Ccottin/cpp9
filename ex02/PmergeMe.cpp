/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:05:22 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/30 18:09:34 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


/*	Constructors */

PmergeMe::PmergeMe(void) : _isodd(false)
{ }

PmergeMe::PmergeMe(PmergeMe const &ref)
{ 
	*this = ref;
}

PmergeMe 	PmergeMe::operator=(PmergeMe const &ref)
{
	if (this != &ref)
	{
		_vector = ref.getVector();
		_vpaired = ref.getVPaired();
		_vsorted = ref.getVSorted();
		_deque = ref.getDeque();
		_dpaired = ref.getDPaired();
		_dsorted = ref.getDSorted();
		_leftover = ref.getLeftover();
		_isodd = ref.getOdd();
		_vtime = ref.getDtime();
		_vtime = ref.getVtime();
	}
	return (*this);
}

PmergeMe::~PmergeMe(void)
{ }


/*	Getters */


std::vector<std::pair<unsigned, unsigned> >	PmergeMe::getVPaired(void) const
{
	return (_vpaired);
}

std::vector<unsigned>					PmergeMe::getVector(void) const
{
	return (_vector);
}

std::vector<unsigned>					PmergeMe::getVSorted(void) const
{
	return (_vsorted);
}

bool									PmergeMe::getOdd(void) const
{
	return (_isodd);
}

unsigned								PmergeMe::getLeftover(void) const
{
	return (_leftover);
}

clock_t									PmergeMe::getVtime(void) const
{
	return (_vtime);
}

/*	Utilities	*/

unsigned	PmergeMe::get_partition_size(unsigned g_size, unsigned p_two)
{
	return (pow(2, p_two) - g_size);
}

void		PmergeMe::printResults(char **av, int ac)
{
	std::cout << "Before : ";
	for (int u = 1 ; u < ac; u++)
		std::cout << av[u] << " ";
	std::cout << std::endl;

	std::cout << "After : ";
	for (std::vector<unsigned>::iterator it = _vsorted.begin() ;
				it != _vsorted.end() ; it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	std::cout.precision(5);
	std::cout << "Time to process a range of " << _vsorted.size()
		<< " elements with std::vector : "
		<< std::fixed << (double)_vtime / CLOCKS_PER_SEC * 1000000 
		<< " us" << std::endl;

	std::cout << "Time to process a range of " << _dsorted.size()
		<< " elements with std::deque  : "
		<< (double)_dtime / CLOCKS_PER_SEC * 1000000 
		<< " us" << std::endl;
}



/*	Vector sort*/




void	PmergeMe::merge(std::vector<std::pair<unsigned, unsigned> >::iterator pos,
				unsigned int size, unsigned int middle)
{
	std::vector<std::pair<unsigned, unsigned> >	tmp;
	unsigned	m, s, i, x;

	m = middle;
	s = size;
	i = 0;
	x = 0;
	tmp.reserve(size);

	while (x < size)
	{
		if (m == size)
			tmp[x] = *(pos + i++);
		else if (i == middle)
			tmp[x] = *(pos + m++);
		else if ((pos + m) < (pos + size) && (pos + m)->first < (pos + i)->first)
			tmp[x] = *(pos + m++);
		else	
			tmp[x] = *(pos + i++);
		++x;
	}
	for (i = 0 ; i < size ; i++)
		*(pos + i) = tmp[i];
}


void	PmergeMe::merge_sort(unsigned size,
						std::vector<std::pair<unsigned, unsigned> >::iterator pos)
{
	int	middle;
   
	if (size < 2)
		return ;
	middle = size / 2;
	merge_sort(middle, pos);
	merge_sort(size - middle, pos + middle);
	merge(pos, size, middle);
}

void	PmergeMe::binary_insert(unsigned insert, std::vector<unsigned>::iterator it,
			std::vector<unsigned>::iterator ite)
{
	std::vector<unsigned>::iterator	mid;

	mid = it + ((ite - it) / 2);
	if (it == ite || insert == *it)
	{
		if (insert != *it && insert > *ite)
			++it;
		_vsorted.insert(it, insert);
		return ;
	}

	if (it == mid && insert < *ite)
		ite = mid;
	else if (it == mid && insert > *it)
		++mid;
	insert < *mid ? binary_insert(insert, it, mid) : binary_insert(insert, mid, ite);
	return ;
}


void	PmergeMe::insert_sort(void)
{
	std::vector<std::pair<unsigned, unsigned> >::iterator it;

	unsigned	g_size;
	unsigned	p_two;
	unsigned	u;

	_vsorted.reserve(_vector.size() + 1);
	it = _vpaired.begin();
	_vsorted.push_back(it->second);
	while (it != _vpaired.end())
	{
		_vsorted.push_back(it->first);
		++it;
	}

	it = _vpaired.begin() + 1;
	if (_vpaired.size() == 2)
		g_size = 1;	
	else
		g_size = 2;
	p_two = 2;
	u = g_size;
	while (it < _vpaired.end())
	{
		--u;
		binary_insert((it + u)->second, _vsorted.begin(),
				(std::find(_vsorted.begin(), _vsorted.end(), (it + u)->first)) - 1);
		if (u == 0)
		{
			it += g_size;
			g_size = get_partition_size(g_size, p_two);
			++p_two;
			u = g_size;
			if (it + u > _vpaired.end())
				u = _vpaired.end() - it;
		}
	}
	if (_isodd)
		binary_insert(_leftover, _vsorted.begin(), _vsorted.end() - 1);
}


void	PmergeMe::sortVector(int ac, char **av) 
{
	unsigned int		index;
	unsigned long int	size;
	int					tmp;
	struct timeval		tv;
	struct timeval		tvb;

	if (gettimeofday(&tvb, NULL))
			exit (1);

	tmp = 1;
	while (tmp < ac)
	{
		size = atoi(av[tmp]);
		if (size > 4294967295)
		{
			std::cout << "Error" << std::endl;
			return ;
		}
		_vector.push_back(size);
		++tmp;
	}

	if (is_sorted(_vector.begin(), _vector.end()))
	{
		_vsorted = _vector;
		if (gettimeofday(&tv, NULL))
			exit (1);
		_vtime = tv.tv_sec * 1000000 + tv.tv_usec - (tvb.tv_sec * 1000000 + tvb.tv_usec);
		return ;
	}
	
	size = _vector.size();
	index = 0;
	std::vector<unsigned >::iterator itt;
	itt = _vector.begin();

	while (size - index > 1)
	{
		if (*(itt + index) > *(itt + index + 1) )
			_vpaired.push_back(std::make_pair(_vector[index], _vector[index + 1]));
		else
			_vpaired.push_back(std::make_pair(_vector[index + 1], _vector[index]));
		index += 2;
	}
	
	if (size - index == 1)
	{
		_leftover = _vector[index];
		_isodd = true;
	}

	merge_sort(_vpaired.size(), _vpaired.begin());
	insert_sort();

	if (gettimeofday(&tv, NULL))
			exit (1);
	_vtime = tv.tv_sec * 1000000 + tv.tv_usec - (tvb.tv_sec * 1000000 + tvb.tv_usec);

/*	uncomment this part to check if it is actually sorted 
	if (is_sorted(_vsorted.begin(), _vsorted.end()))
	std::cout << "isGood, size =  " << _vsorted.size() << "\n";
*/
}
