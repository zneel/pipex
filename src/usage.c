/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 01:08:23 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 01:08:53 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	write(2, "usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
}

void	check_args(int ac)
{
	if (ac != 5)
	{
		print_usage();
		exit(1);
	}
}
