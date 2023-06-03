/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:17:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/03 18:06:54 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_cmds(t_list *cmds)
{
	while (cmds)
	{
		waitpid(-1, 0, 0);
		cmds = cmds->next;
	}
}

void	do_pipes(int fd[2], pid_t pid)
{
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			perror("dup2 child");
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], 0) == -1)
			perror("dup2 parent");
		close(fd[0]);
	}
}

int	pipe_fork(t_cmd *cmd, pid_t *pid, int fd[2], t_pipe *p)
{
	if (cmd->has_pipe && pipe(fd) != 0)
	{
		perror("pipe");
		return (0);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd->has_pipe)
		do_pipes(fd, *pid);
	else
	{
		close(fd[0]);
		close(fd[1]);
		dup2(p->fdout, 1);
		close(p->fdout);
	}
	return (1);
}

void	execute(t_cmd *cmd, char **env)
{
	int		err;
	char	**full_cmd;

	full_cmd = get_cmd(cmd->raw_cmd, env);
	if (!full_cmd || !*full_cmd)
		return (perror("command not found"), exit(errno));
	cmd->cmd = full_cmd;
	err = execve(cmd->cmd[0], cmd->cmd, env);
	if (err == -1)
	{
		cmd_clean(cmd);
		perror("command error");
		exit(errno);
	}
}
