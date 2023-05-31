/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:41:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/05/31 19:38:47 by ebouvier         ###   ########.fr       */
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
	return (0);
}


void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	execute(char *full_cmd, char **env)
{
	char	**cmd;
	int		err;

	cmd = ft_split(full_cmd, " ");
	err = access(cmd[0], F_OK | X_OK) != 0;
	if (err != 0)
	{
		perror("cannot execute command");
		exit(errno);
	}
	else
	{
		err = execve(cmd[0], cmd, env);
		if (err)
		{
			perror(strerror(err));
			free_split(cmd);
			exit(errno);
		}
		free_split(cmd);
		exit(0);
	}
}

void	exec_parent(t_pipe *p, char *full_cmd, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute(full_cmd, p->env);
}

void	exec_child(t_pipe *p, char *full_cmd, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(full_cmd, p->env);
}

void	do_shit(t_pipe *p)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 2;
	dup2(p->fd1, STDIN_FILENO);
	dup2(p->fd2, STDOUT_FILENO);
	while (i < p->ac - 1)
	{
		if (pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
		{
			perror("error when forking");
			return ;
		}
		if (pid == 0)
			exec_child(p, p->av[i], fd);
		else
			exec_parent(p, p->av[++i], fd);
		close(fd[0]);
		close(fd[1]);
	}
	wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	px;

	check_args(ac);
	if (parse_av(ac, av, env, &px) < 0)
		exit(errno);
	do_shit(&px);
	return (0);
}
