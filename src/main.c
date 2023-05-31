/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:41:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/05/31 21:04:47 by ebouvier         ###   ########.fr       */
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
		perror("command error");
		exit(errno);
	}
	else
	{
		err = execve(cmd[0], cmd, env);
		if (err)
		{
			perror("error");
			free_split(cmd);
			exit(errno);
		}
		free_split(cmd);
		exit(0);
	}
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	open_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("error when forking");
		return (pid);
	}
	return (pid);
}

void	pipe_commands(t_pipe *p)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 2;
	while (++i < p->ac - 2)
	{
		if (pipe(fd) == -1)
			return ;
		pid = open_fork();
		if (pid < 0)
			return (close_pipe(fd));
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execute(p->av[i], p->env);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
		close_pipe(fd);
	}
	execute(p->av[i], p->env);
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
