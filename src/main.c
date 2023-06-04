/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:41:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/04 21:09:27 by ebouvier         ###   ########.fr       */
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

int	parse_av(int ac, char **av, char **env, t_pipe *p)
{
	p->fd_in = open(av[1], O_RDONLY);
	p->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fd_in < 0 || p->fd_out < 0)
	{
		perror("filedes error");
		return (-1);
	}
	p->ac = ac;
	p->av = av;
	p->env = env;
	p->in_save = dup(0);
	return (0);
}

void	cleanup(t_pipe *p)
{
	close(p->fd_in);
	dup2(p->in_save, 0);
	close(p->in_save);
	close(p->fd_out);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	p;

	check_args(ac);
	if (parse_av(ac, av, env, &p) < 0)
		exit(errno);
	pipex(&p);
	cleanup(&p);
	return (0);
}
