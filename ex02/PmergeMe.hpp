/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:06:11 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/28 15:18:22 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <cctype>
# include <cstring>
# include <vector>
# include <deque>
# include <cstdlib>
# include <cmath>
# include <algorithm>
# include <set>
# include <ctime>
#include <sys/time.h>

class	PmergeMe
{
	public:

		/*constructors*/

		PmergeMe(void);
		PmergeMe(PmergeMe const &ref);
		PmergeMe	operator=(PmergeMe const &ref);
		~PmergeMe(void);

		/*getters*/

		std::deque<std::pair<unsigned, unsigned> >	getDPaired(void)	const;
		std::vector<std::pair<unsigned, unsigned> >	getVPaired(void)	const;
		std::deque<unsigned>						getDeque(void)		const;
		std::vector<unsigned int>					getVector(void)		const;
		std::deque<unsigned>						getDSorted(void)	const;
		std::vector<unsigned>						getVSorted(void)	const;
		time_t										getDtime(void)		const;
		time_t										getVtime(void)		const;

		bool										getOdd(void)		const;
		unsigned									getLeftover(void)	const;
	
		/*start sort*/

		void							sortVector(int ac, char **av);
		void							sortDeque(int ac, char **av);
		void							printResults(char **av, int ac);

	private:


		/*vector sort*/

		void	merge_sort(unsigned size,
					std::vector<std::pair<unsigned, unsigned> >::iterator pos);

		void	merge(std::vector<std::pair<unsigned, unsigned> >::iterator pos,
					unsigned int size, unsigned int middle);
		
		void	insert_sort(void);
		
		void	binary_insert(unsigned insert, std::vector<unsigned>::iterator it,
					std::vector<unsigned>::iterator ite);
		

		std::vector<unsigned int>							_vector;
		std::vector<unsigned int>							_vsorted;
		std::vector<std::pair<unsigned int, unsigned int> >	_vpaired;
		clock_t												_vtime;

		
		/*deque sort*/

		void	merge_sort2(unsigned size,
					std::deque<std::pair<unsigned, unsigned> >::iterator pos);
		
		void	merge2(std::deque<std::pair<unsigned, unsigned> >::iterator pos,
					unsigned int size, unsigned int middle);

		void	binary_insert2(unsigned insert, std::deque<unsigned>::iterator it,
					std::deque<unsigned>::iterator ite);

		void	insert_sort2(void);

		std::deque<unsigned int>							_deque;
		std::deque<unsigned int>							_dsorted;
		std::deque<std::pair<unsigned int, unsigned int> >	_dpaired;
		clock_t												_dtime;



		/*commons functions*/

		template <class ForwardIterator>
		bool is_sorted (ForwardIterator first, ForwardIterator last)
		{
			if (first == last)
				return (true);

			ForwardIterator next;
			next = first;
			while (++next != last)
			{
				if (*next < *first)
					return (false);
				++first;
			}
			return (true);
		}

		unsigned	get_partition_size(unsigned g_size, unsigned p_two);

		unsigned									_leftover;
		bool										_isodd;
};

#endif
