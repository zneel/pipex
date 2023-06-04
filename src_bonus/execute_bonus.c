/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:17:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 00:48:12 by ebouvier         ###   ########.fr       */
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
		close(p->fd_in);
		exit(errno);
	}
	cmd->cmd = full_cmd;
	err = execve(cmd->cmd[0], cmd->cmd, p->env);
	if (err == -1)
	{
		cmds_clean(cmds);
		perror("command error");
		close(p->fd_in);
		exit(errno);
	}
}

void	pipe_exec(t_cmd *cmd, int pipe_fd[2], t_pipe *p, t_list *cmds)
{
	close(p->in_save);
	if (cmd->has_pipe)
		close(p->fd_out);
	if (cmd->index == 0)
	{
		prepare_fd(p);
		pipe_for_first(pipe_fd);
	}
	else if (cmd->has_pipe)
		pipe_for_child(p->previous_out, pipe_fd);
	else
		pipe_for_last(pipe_fd, p);
	execute(cmds, cmd, p);
}
