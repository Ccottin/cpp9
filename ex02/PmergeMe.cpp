/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:05:22 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/26 18:06:48 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{ }

PmergeMe::PmergeMe(int ac, char **av)
{
	int	tmp;

	tmp = 1;
	while (tmp < ac + 1)
	{
		_vector.push_back(atoi(av[tmp]));
		++tmp;
	}
	while (ac > 0)
	{
		_deque.push_front(atoi(av[ac]));
		--ac;
	}
	_isodd = false;
}

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
	}
	return (*this);
}

PmergeMe::~PmergeMe(void)
{ }

std::vector<std::pair<unsigned, unsigned> >	PmergeMe::getVPaired(void) const
{
	return (_vpaired);
}

std::vector<unsigned>					PmergeMe::getVector(void) const
{
	return (_vector);
}

unsigned	PmergeMe::get_partition_size(unsigned g_size, unsigned p_two)
{
//	std::cout << "new partit. size = " << (pow(2, p_two) - g_size) << std::endl;
	return (pow(2, p_two) - g_size);
}
	/*vector sort*/

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
/*	std::cout << "merge operation == \n";
	std::vector<std::pair<unsigned, unsigned> >::iterator it = tmp.begin();
	while(it != tmp.end())
	{
		std::cout << it->first << "     " << it->second << std::endl;
		it++;
	}*/
	for (i = 0 ; i < size ; i++)
		*(pos + i) = tmp[i];

	/*it = _vpaired.begin();
	while(it != _vpaired.end())
	{
		std::cout << it->first << "     " << it->second << std::endl;
		it++;
	}*/
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

void	PmergeMe::insert_odd(void)
{
	std::vector<unsigned>::iterator	it;
	std::vector<unsigned>::iterator	ite;
	unsigned						size;

	size = _vsorted.size() / 2;
	it = _vsorted.begin() + size;
	ite = _vsorted.begin() + size;
	while (size > 1)
	{
		size = size / 2;
		if (*ite > _leftover)
			ite += size;
		else
			it -= size;
	}
	_vsorted.insert(it, _leftover);

}

void	PmergeMe::binary_insert(unsigned insert, std::vector<unsigned>::iterator it,
			std::vector<unsigned>::iterator ite)
{
	std::vector<unsigned>::iterator	mid;

	mid = it + ((ite - it) / 2);
	std::cout <<"mid = " << *mid << " it puis ite ==" << *it << "  " << *ite << "  insert = " << insert << std::endl;

	if (it == ite)
	{
		std::cout << "here : it = " << *it << "  ite = " << *ite;
		if (insert > *ite)
			++it;
		_vsorted.insert(it, insert);
		std::cout << "  sorted = ";
		for (it = _vsorted.begin(), ite = _vsorted.end() ; it != ite; it++)
			std::cout << "  " << *it;
		std::cout << std::endl;

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


	std::vector<unsigned >::iterator itt = _vector.begin();
/*		itt = _vsorted.begin();
		while (itt != _vsorted.end())
		{
			std::cout << *itt << "     ";
			++itt;
		}
*/


	it = _vpaired.begin() + 1;
	g_size = 2;
	p_two = 2;
	u = g_size;
	while (it < _vpaired.end())
	{
		--u;
		std::cout << "u = " << u << " truc = " << (it + u)->first << std::endl;
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
		itt = _vsorted.begin();
		while (itt != _vsorted.end())
		{
			std::cout << *itt << "     ";
			++itt;
		}
	}
	if (_isodd)
	{
		std::cout << "isodd\n";
		binary_insert(_leftover, _vsorted.begin(), _vsorted.end() - 1);
	}
}

void	PmergeMe::sortVector(void) 
{
	unsigned int	index;
	unsigned int	size;

	size = _vector.size();
	index = 0;
	std::vector<unsigned >::iterator itt = _vector.begin();
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

	std::vector<std::pair<unsigned, unsigned> >::iterator it = _vpaired.begin();
/*	std::cout << "before sort\n";
	while(it != _vpaired.end())
	{
		std::cout << it->first << "     " << it->second << std::endl;
		it++;
	}
*/
	merge_sort(_vpaired.size(), _vpaired.begin());
	std::cout << "\naftere sort\n";

	it = _vpaired.begin();
	while (it != _vpaired.end())
	{
		std::cout << it->first << "     " << it->second << std::endl;
		++it;
	}

	insert_sort();
	
	std::cout << "\nfinal sort\n";
	itt = _vsorted.begin();
	while (itt != _vsorted.end())
	{
		std::cout << *itt << "     ";
		++itt;
	}
	if (std::is_sorted(_vsorted.begin(), _vsorted.end()))
		std::cout << "isGood, size =  " << _vsorted.size() << "\n";
}
