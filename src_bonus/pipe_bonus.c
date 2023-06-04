/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 00:50:27 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*parse_cmds(t_pipe *p)
{
	t_list	*cmds;
	t_cmd	*cmd;
	int		i;
	int		has_pipe;

	if (p->here_doc == 1)
		i = 3;
	else
		i = 2;
	cmds = NULL;
	while (i < p->ac - 1)
	{
		has_pipe = i < p->ac - 2;
		cmd = new_cmd(p->av[i], has_pipe, i);
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
	int		pipe_fd[2];

	cmds = parse_cmds(p);
	if (!cmds)
		exit(errno);
	curr_cmd = cmds;
	while (curr_cmd)
	{
		if (((t_cmd *)curr_cmd->content)->has_pipe)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			pipe_exec((t_cmd *)curr_cmd->content, pipe_fd, p, cmds);
		if (((t_cmd *)curr_cmd->content)->has_pipe)
			p->previous_out = pipe_fd[READ];
		curr_cmd = curr_cmd->next;
	}
	close_pipe(pipe_fd);
	wait_for_cmds(cmds, p);
	cmds_clean(cmds);
}
