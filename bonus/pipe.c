/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 08:59:55 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		free_split(cmd);
		exit(errno);
	}
	else
	{
		err = execve(cmd[0], cmd, env);
		if (err == -1)
		{
			perror("error");
			free_split(cmd);
			exit(errno);
		}
		free_split(cmd);
		exit(0);
	}
}

int	open_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("error when forking");
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
	wait(NULL);
	execute(p->av[i], p->env);
}
