/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:46:29 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/04 21:09:24 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	write(2, "usage: ./pipex_bonus infile cmd1 cmd2 cmdN outfile\n", 52);
}

void	print_here_doc(void)
{
	write(2, "usage: ./pipex_bonus here_doc LIMITER cmd1 cmd2 outfile\n", 57);
}

void	check_args_bonus(int ac, char **av)
{
	if (ac < 4)
	{
		print_usage();
		print_here_doc();
		exit(1);
	}
	else if (ac != 6 && check_here_doc(av[1]))
	{
		print_here_doc();
		exit(1);
	}
}