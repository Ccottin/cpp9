/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DPmergeMe.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:59:18 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/30 18:12:35 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*	Getters */


std::deque<std::pair<unsigned, unsigned> >	PmergeMe::getDPaired(void) const
{
	return (_dpaired);
}

std::deque<unsigned>					PmergeMe::getDeque(void) const
{
	return (_deque);
}

std::deque<unsigned>					PmergeMe::getDSorted(void) const
{
	return (_dsorted);
}

clock_t									PmergeMe::getDtime(void) const
{
	return (_dtime);
}

/*	Deque sort */

void	PmergeMe::binary_insert2(unsigned insert, std::deque<unsigned>::iterator it,
			std::deque<unsigned>::iterator ite)
{
	std::deque<unsigned>::iterator	mid;

	mid = it + ((ite - it) / 2);
	if (it == ite || insert == *it)
	{
		if (insert != *it && insert > *ite)
			++it;
		_dsorted.insert(it, insert);
		return ;
	}

	else if (it == mid && insert < *ite)
		ite = mid;
	else if (it == mid && insert > *it)
		++mid;
	insert < *mid ? binary_insert2(insert, it, mid) : binary_insert2(insert, mid, ite);
	return ;
}

void	PmergeMe::insert_sort2(void)
{
	std::deque<std::pair<unsigned, unsigned> >::iterator it;
	unsigned	g_size;
	unsigned	p_two;
	unsigned	u;

	it = _dpaired.begin();
	while (it != _dpaired.end())
	{
		_dsorted.push_back(it->first);
		++it;
	}
	_dsorted.push_front(_dpaired.begin()->second);
	it = _dpaired.begin() + 1;
	if (_vpaired.size() == 2)
		g_size = 1;	
	else
		g_size = 2;
	p_two = 2;
	u = g_size;
	while (it < _dpaired.end())
	{
		--u;
		binary_insert2((it + u)->second, _dsorted.begin(),
				(std::find(_dsorted.begin(), _dsorted.end(), (it + u)->first)) - 1);
		if (u == 0)
		{
			it += g_size;
			g_size = get_partition_size(g_size, p_two);
			++p_two;
			u = g_size;
			if (it + u > _dpaired.end())
				u = _dpaired.end() - it;
		}
	}
	if (_isodd)
		binary_insert2(_leftover, _dsorted.begin(), _dsorted.end() - 1);

}

void	PmergeMe::merge2(std::deque<std::pair<unsigned, unsigned> >::iterator pos,
			unsigned int size, unsigned int middle)
{
	std::deque<std::pair<unsigned, unsigned> >	tmp;
	unsigned	m, s, i;

	m = middle;
	s = size;
	i = 0;

	while (tmp.size() < size)
	{
		if (m == size)
			tmp.push_back(*(pos + i++));
		else if (i == middle)
			tmp.push_back(*(pos + m++));
		else if ((pos + m) < (pos + size) && (pos + m)->first < (pos + i)->first)
			tmp.push_back(*(pos + m++));
		else	
			tmp.push_back(*(pos + i++));
	}
	for (i = 0 ; i < size ; i++)
		*(pos + i) = tmp[i];

}

void	PmergeMe::merge_sort2(unsigned size, std::deque<std::pair<unsigned, unsigned> >::iterator pos)
{
	int	middle;

	if (size < 2)
		return ;
	middle = size / 2;
	merge_sort2(middle, pos);
	merge_sort2(size - middle, pos + middle);
	merge2(pos, size, middle);
}

void	PmergeMe::sortDeque(int ac, char **av)
{
	unsigned long int	size;
	unsigned int		index;
	struct timeval		tv;
	struct timeval		tvb;

	if (gettimeofday(&tvb, NULL))
			exit (1);
	--ac;
	while (ac > 0)
	{
		size = atoi(av[ac]);
		if (size > 4294967295)
			return ;
		_deque.push_front(size);
		--ac;
	}

		
	if (is_sorted(_deque.begin(), _deque.end()))
	{
		_dsorted = _deque;
		if (gettimeofday(&tv, NULL))
			exit (1);
		_dtime = tv.tv_sec * 1000000 + tv.tv_usec - (tvb.tv_sec * 1000000 + tvb.tv_usec);
		return ;
	}

	size = _deque.size();
	index = 0;
	std::deque<unsigned >::iterator it;
	it = _deque.begin();

	while (size - index > 1)
	{
		if (*(it + index) > *(it + index + 1) )
			_dpaired.push_back(std::make_pair(_deque[index], _deque[index + 1]));
		else
			_dpaired.push_back(std::make_pair(_deque[index + 1], _deque[index]));
		index += 2;
	}
	/*technically we don't need to di this here, but time will be
	  falsed if we don't so we do */
	if (size - index == 1)
	{
		_leftover = _deque[index];
		_isodd = true;
	}
				
	merge_sort2(_dpaired.size(), _dpaired.begin());
	insert_sort2();

	if (gettimeofday(&tv, NULL))
			exit (1);
	_dtime = tv.tv_sec * 1000000 + tv.tv_usec - (tvb.tv_sec * 1000000 + tvb.tv_usec);

/*	uncomment this part to check if it is actually sorted 
	if (is_sorted(_dsorted.begin(), _dsorted.end()))
		std::cout << "isGood, size =  " << _dsorted.size() << "\n";
*/
}
