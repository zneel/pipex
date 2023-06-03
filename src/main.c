/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:41:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/03 18:04:11 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(void)
{
	write(2, "usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
}

void	check_args(int ac, char **env)
{
	if (!env || !*env)
	{
		write(2, "env not set\n", 13);
		exit(1);
	}
	if (ac < 5)
	{
		print_usage();
		exit(1);
	}
}

int	parse_av(int ac, char **av, char **env, t_pipe *p)
{
	p->fdin = open(av[1], O_RDONLY);
	p->fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fdin < 0 || p->fdout < 0)
	{
		perror("filedes error");
		return (-1);
	}
	p->ac = ac;
	p->av = av;
	p->env = env;
	p->in_save = dup(0);
	p->out_save = dup(1);
	return (0);
}

void	clean(t_pipe *p)
{
	close(p->in_save);
	close(p->out_save);
	close(p->fdin);
	close(p->fdout);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	p;

	check_args(ac, env);
	if (parse_av(ac, av, env, &p) < 0)
		exit(errno);
	pipex(&p);
	clean(&p);
	return (0);
}
