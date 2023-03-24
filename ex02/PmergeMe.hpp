/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:06:11 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/24 22:45:10 by ccottin          ###   ########.fr       */
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


		std::vector<unsigned int>					_vector;
		std::vector<std::pair<unsigned int, unsigned int> >	_paired;

		/*deque sort*/
		std::deque<unsigned int>					_deque;
		unsigned									_leftover;
};

#endif
