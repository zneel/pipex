/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/03 17:59:24 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

t_list	*parse_cmds(t_pipe *p)
{
	t_list	*cmds;
	t_cmd	*cmd;
	int		i;
	int		has_pipe;

	i = 2;
	cmds = NULL;
	while (i < p->ac - 1)
	{
		has_pipe = i < p->ac - 2;
		cmd = new_cmd(p->av[i], has_pipe);
		if (!cmd)
			return (ft_lstclear(&cmds, (void *)cmd_clean), NULL);
		if (!add_cmd(&cmds, cmd))
			return (free(cmd), ft_lstclear(&cmds, (void *)cmd_clean), NULL);
		i++;
	}
	return (cmds);
}

void	pipex(t_pipe *p)
{
	t_list	*cmds;
	t_list	*curr_cmd;
	pid_t	pid;
	t_cmd	*cmd;
	int		fd[2];

	dup2(p->fdin, 0);
	close(p->fdin);
	cmds = parse_cmds(p);
	if (!cmds)
		exit(errno);
	curr_cmd = cmds;
	while (curr_cmd)
	{
		cmd = curr_cmd->content;
		if (!pipe_fork(cmd, &pid, fd, p))
			return (cmds_clean(cmds), exit(errno));
		if (pid == 0)
			execute(cmd, p->env);
		curr_cmd = curr_cmd->next;
	}
	dup2(p->in_save, 0);
	dup2(p->out_save, 1);
	close(p->in_save);
	close(p->out_save);
	wait_for_cmds(cmds);
	cmds_clean(cmds);
}
