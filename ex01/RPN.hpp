/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:50:49 by ccottin           #+#    #+#             */
/*   Updated: 2023/03/23 19:23:56 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream> 
# include <string>
# include <vector>
# include <cctype>
# include <cstdlib>

class	RPN {

	public :

		RPN(void);
		RPN(RPN const &ref);
		RPN &operator=(RPN const &ref);
		~RPN(void);

		std::vector<long int>	getRes(void) const;
		int						launch(std::string line);

	private :

		std::vector<long int>	_res;	
		
		void	calculate(char sign);
		void	print_elems(void);
};

#endif
