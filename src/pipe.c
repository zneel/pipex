/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 11:52:15 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *s)
{
	perror(s);
	exit(errno);
}

int	execute(char *full_cmd, char **env)
{
	int		err;
	char	**cmd;

	cmd = get_cmd(full_cmd, env);
	if (!cmd || !*cmd)
		error_exit("command not found");
	err = execve(cmd[0], cmd, env);
	free_split(cmd);
	if (err == -1)
		error_exit("error executing command");
	exit(0);
}

int	open_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("error when forking");
	return (pid);
}

void	child(int fd[2], t_pipe *p, int i)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(p->av[i], p->env);
}

void	parent(int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

void	pipe_commands(t_pipe *p)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 1;
	while (++i < p->ac - 2)
	{
		if (pipe(fd) == -1)
			return ;
		pid = open_fork();
		if (pid < 0)
			return (close_pipe(fd), exit(errno));
		if (pid == 0)
			child(fd, p, i);
		else
			parent(fd);
		close_pipe(fd);
	}
	execute(p->av[i], p->env);
}
