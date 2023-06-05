/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:17:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 16:32:43 by ebouvier         ###   ########.fr       */
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

void	pipe_exec(t_cmd *cmd, int pipe_fd[2], t_pipe *p)
{
	close(p->in_save);
	if (cmd->index == 0)
		pipe_for_first(pipe_fd, p);
	else if (cmd->has_pipe)
		pipe_for_child(p->previous_out, pipe_fd, p);
	else
		pipe_for_last(pipe_fd, p);
	execute(cmd, p->env);
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
