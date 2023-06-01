/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:16:24 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 23:54:07 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//delete after
void	print_t_cmd(t_cmd *cmd)
{
	printf("PID: %d\n", cmd->pid);
	if (cmd->cmd != NULL)
	{
		printf("CMD: ");
		for (int i = 0; cmd->cmd[i] != NULL; i++)
			printf("%s ", cmd->cmd[i]);
		printf("\n");
	}
	printf("HAS_PIPE: %d\n", cmd->has_pipe);
	printf("RAW_CMD: %s\n", cmd->raw_cmd);
}

t_cmd	*new_cmd(char *raw_cmd, int has_pipe)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->has_pipe = has_pipe;
	new_cmd->raw_cmd = ft_strdup(raw_cmd);
	new_cmd->pid = -1;
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
