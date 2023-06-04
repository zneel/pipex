/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:41:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/04 20:47:17 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipe(t_pipe *p)
{
	p->ac = 0;
	p->av = NULL;
	p->env = NULL;
	p->fd_in = -1;
	p->fd_out = -1;
	p->in_save = -1;
	p->here_doc = 0;
	p->limiter = NULL;
	p->previous_out = -1;
}

int	parse_av(int ac, char **av, char **env, t_pipe *p)
{
	p->ac = ac;
	p->av = av;
	p->env = env;
	if (check_here_doc(p->av[1]))
		p->here_doc = 1;
	if (p->here_doc)
		handle_here_doc(p);
	else
		p->fd_in = open(p->av[1], O_RDONLY);
	p->fd_out = open(p->av[p->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fd_in < 0 || p->fd_out < 0)
	{
		perror("filedes error");
		return (-1);
	}
	p->in_save = dup(0);
	return (0);
}

void	cleanup(t_pipe *p)
{
	dup2(p->in_save, 0);
	close(p->in_save);
	close(p->fd_out);
	if (p->here_doc)
	{
		free(p->limiter);
		if (unlink(HERE_DOC_PATH) < 0)
		{
			perror("unlink");
			exit(errno);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	p;

	check_args_bonus(ac, av);
	init_pipe(&p);
	if (parse_av(ac, av, env, &p) < 0)
		exit(errno);
	pipex(&p);
	cleanup(&p);
	return (0);
}
