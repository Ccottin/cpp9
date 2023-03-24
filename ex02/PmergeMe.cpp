/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:05:22 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/24 22:56:45 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{ }

PmergeMe::PmergeMe(int ac, char **av)
{
	int	tmp;

	tmp = 0;
	while (tmp < ac)
	{
		_vector.push_back(atoi(av[ac]));
		++tmp;
	}
	while (ac > 0)
	{
		_deque.push_front(atoi(av[ac]));
		--ac;
	}
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
		_paired = ref.getVPaired();
	}
	return (*this);
}

PmergeMe::~PmergeMe(void)
{ }

std::vector<std::pair<unsigned, unsigned> >	PmergeMe::getVPaired(void) const
{
	return (_paired);
}

std::vector<unsigned>					PmergeMe::getVector(void) const
{
	return (_vector);
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
//		std::cout << " HEREEEE
		if (m == size)
			tmp[x] = *(pos + i++);
		else if (i == middle)
			tmp[x] = *(pos + m++);
		//pb indexag
		else if ((pos + m) < (pos + size) && (pos + m)->first < (pos + i)->first)
			tmp[x] = *(pos + m++);
		else	
			tmp[x] 
				= *(pos + i++);
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

void	PmergeMe::sortVector(void)
{
	unsigned int	index;
	unsigned int	size;

	size = _vector.size();
	index = 0;
	while (size - index > 1)
	{
		if (index > index + 1)
			_paired.push_back(std::make_pair(_vector[index], _vector[index + 1]));
		else
			_paired.push_back(std::make_pair(_vector[index + 1], _vector[index]));
		index += 2;
	}
	if (size - (index - 2) == 1)
		_leftover = _vector[index - 2];
	merge_sort(_paired.size(), _paired.begin());
	
	std::vector<std::pair<unsigned, unsigned> >::iterator	it = _paired.begin();
	while (it != _paired.end())
	{
		std::cout << it->first << "     ";
		++it;
	}
}
