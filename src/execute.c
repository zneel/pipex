/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:17:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 23:55:01 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_cmds(t_list *cmds, t_pipe *p)
{
	while (cmds)
	{
		waitpid(-1, &p->last_status, 0);
		cmds = cmds->next;
	}
}

void	execute(t_list *cmds, t_cmd *cmd, t_pipe *p)
{
	int		err;
	char	**full_cmd;

	full_cmd = get_cmd(cmd->raw_cmd, p->env);
	if (!full_cmd || !*full_cmd)
	{
		cmds_clean(cmds);
		perror("command not found");
		exit(errno);
	}
	cmd->cmd = full_cmd;
	err = execve(cmd->cmd[0], cmd->cmd, p->env);
	if (err == -1)
	{
		cmds_clean(cmds);
		perror("command error");
		exit(errno);
	}
}

void	pipe_exec(t_cmd *cmd, int pipes[2][2], t_pipe *p, t_list *cmds)
{
	int	cmd_index;

	cmd_index = cmd->index;
	if (p->here_doc)
		cmd_index--;
	if (cmd_index == 0)
	{
		close(p->fd_out);
		pipe_for_first(pipes[NEW], p->fd_in);
	}
	else if (cmd->has_pipe)
	{
		close(p->fd_in);
		close(p->fd_out);
		pipe_for_child(pipes[NEW], pipes[OLD]);
	}
	else
	{
		close(p->fd_in);
		pipe_for_last(pipes[OLD], p->fd_out);
	}
	execute(cmds, cmd, p);
}
