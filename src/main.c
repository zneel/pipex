/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:41:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 13:52:41 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	ft_printf("usage: ./pipex infile cmd1 cmd2 outfile\n");
}

void	check_args(int ac)
{
	if (ac < 5)
	{
		print_usage();
		exit(0);
	}
}

int	parse_av(int ac, char **av, char **env, t_pipe *p)
{
	p->fd1 = open(av[1], O_RDONLY);
	p->fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (p->fd1 < 0 || p->fd2 < 0)
	{
		perror("filedes error");
		return (-1);
	}
	p->ac = ac;
	p->av = av;
	p->env = env;
	dup2(p->fd1, STDIN_FILENO);
	dup2(p->fd2, STDOUT_FILENO);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	p;
	int		in;

	in = dup(STDIN_FILENO);
	check_args(ac);
	if (parse_av(ac, av, env, &p) < 0)
		exit(errno);
	pipe_commands(&p);
	dup2(in, STDIN_FILENO);
	close(p.fd1);
	close(p.fd2);
	return (0);
}
