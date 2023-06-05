/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 23:42:05 by ebouvier         ###   ########.fr       */
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

void	init_pipes(int pipes[2][2])
{
	pipes[OLD][READ] = -1;
	pipes[OLD][WRITE] = -1;
	pipes[NEW][READ] = -1;
	pipes[NEW][WRITE] = -1;
}

void	parent_handler(int has_pipe, int pipes[2][2])
{
	close_if_open(pipes[OLD][READ]);
	if (has_pipe)
	{
		pipes[OLD][READ] = pipes[NEW][READ];
		pipes[NEW][READ] = -1;
		close_if_open(pipes[NEW][WRITE]);
	}
	else
		pipes[OLD][READ] = -1;
}

int	exec_all_commands(t_list *cmds, t_pipe *p)
{
	t_list	*curr_cmd;
	int		pid;
	int		pipes[2][2];

	curr_cmd = cmds;
	init_pipes(pipes);
	while (curr_cmd)
	{
		if (((t_cmd *)(curr_cmd->content))->has_pipe)
			if (pipe(pipes[NEW]) == -1)
				return (0);
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
			pipe_exec(curr_cmd->content, pipes, p, cmds);
		else
			parent_handler(((t_cmd *)(curr_cmd->content))->has_pipe, pipes);
		curr_cmd = curr_cmd->next;
	}
	return (1);
}

void	pipex(t_pipe *p)
{
	t_list	*cmds;

	cmds = parse_cmds(p);
	if (!cmds)
		exit(errno);
	if (!exec_all_commands(cmds, p))
	{
		cmds_clean(cmds);
		exit(errno);
	}
	wait_for_cmds(cmds, p);
	cmds_clean(cmds);
}
