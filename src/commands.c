/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:16:24 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/02 10:56:33 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*new_cmd(char *raw_cmd, int has_pipe)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->has_pipe = has_pipe;
	new_cmd->raw_cmd = ft_strdup(raw_cmd);
	return (new_cmd);
}
void	cmd_clean(t_cmd *cmd)
{
	free(cmd->raw_cmd);
	if (cmd->cmd)
		free_split(cmd->cmd);
	free(cmd);
}

int	add_cmd(t_list **cmds, t_cmd *cmd)
{
	t_list	*new;

	new = ft_lstnew(cmd);
	if (!new)
		return (0);
	ft_lstadd_back(cmds, new);
	return (1);
}

void	cmds_clean(t_list *cmds)
{
	ft_lstclear(&cmds, (void *)cmd_clean);
}
