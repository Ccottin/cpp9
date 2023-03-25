/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:06:11 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/25 16:08:43 by ccottin          ###   ########.fr       */
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

class	PmergeMe
{
	public:

		/*constructors*/

		PmergeMe(void);
		PmergeMe(int ac, char **av);
		PmergeMe(PmergeMe const &ref);
		PmergeMe	operator=(PmergeMe const &ref);
		~PmergeMe(void);

		/*getters*/

		std::vector<std::pair<unsigned int, unsigned int> >	getVPaired(void) const;
		std::vector<unsigned int>					getVector(void) const;
	
		/*start sort*/

		void							sortVector(void);

	private:


		/*vector sort*/

		void	merge_sort(unsigned size,
					std::vector<std::pair<unsigned, unsigned> >::iterator pos);
		void	merge(std::vector<std::pair<unsigned, unsigned> >::iterator pos,
					unsigned int size, unsigned int middle);
		void	insert_sort(void);
		void	binary_insert(std::pair<unsigned, unsigned> insert);
		void	insert_odd(void);


		std::vector<unsigned int>					_vector;
		std::vector<unsigned int>					_vsorted;
		std::vector<std::pair<unsigned int, unsigned int> >	_vpaired;

		/*deque sort*/
		std::deque<unsigned int>					_deque;
		unsigned									_leftover;
		bool										_isodd;


		/*utilitaries functions*/

		unsigned	get_partition_size(unsigned g_size, unsigned p_two);

};

#endif
