/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/02 10:54:39 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

/**
 * @brief Parses commands from a pipe structure.
 *
 * Extracts commands from the given pipe structure and creates a linked list
 * of command structures.
 *
 * @param p Pointer to the pipe structure containing the command arguments.
 * @return Pointer to the linked list of commands, or NULL on error.
 */
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
	close(STDIN_FILENO);
	wait_for_cmds(cmds);
	cmds_clean(cmds);
}
