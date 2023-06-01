/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 18:16:27 by ebouvier         ###   ########.fr       */
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

int	do_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("error when forking");
	return (pid);
}

void	child(int fd[2], char *full_cmd, char **env)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(full_cmd, env);
}

void	wait_all_childs(int child_count)
{
	int	i;

	i = 0;
	while (i++ < child_count)
		wait(NULL);
}

void	pipe_commands(t_pipe *p)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 2;
	fd[0] = 0;
	fd[1] = 0;
	while (i < p->ac - 1)
	{
		if (i < p->ac - 2 && pipe(fd) == -1)
			return ;
		pid = do_fork();
		if (pid == -1)
			return (exit_error(fd));
		if (pid == 0)
			child(fd, p->av[i], p->env);
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			i++;
		}
		close_pipe(fd);
	}
	wait_all_childs(i - 2);
}
