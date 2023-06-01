/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:56:11 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 16:54:18 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *s)
{
	perror(s);
	exit(errno);
}

int	execute(char *full_cmd, char **env)
{
	int		err;
	char	**cmd;

	cmd = get_cmd(full_cmd, env);
	if (!cmd || !*cmd)
		error_exit("command not found");
	err = execve(cmd[0], cmd, env);
	free_split(cmd);
	if (err == -1)
		error_exit("error executing command");
	exit(0);
}

int	add_child(pid_t pid, t_list **child_lst)
{
	pid_t	*pid_ptr;
	t_list	*new_node;

	pid_ptr = malloc(sizeof(pid_t));
	if (!pid_ptr)
		return (-1);
	*pid_ptr = pid;
	new_node = ft_lstnew(pid_ptr);
	if (!new_node)
		return (free(pid_ptr), -1);
	ft_lstadd_back(child_lst, new_node);
	return (1);
}

int	do_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("error when forking");
	return (pid);
}

void	child(int fd[2], char *full_cmd, char **env)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(full_cmd, env);
}

void	parent(int fd[2], pid_t pid, t_list **child_lst)
{
	if (add_child(pid, child_lst) == -1)
		return (free_child_exit(child_lst, fd));
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

void	wait_all_childs(t_list *child_lst)
{
	while (child_lst)
	{
		ft_printf("waiting:%d\n", *(int *)child_lst->content);
		waitpid(*(int *)child_lst->content, NULL, 0);
		child_lst = child_lst->next;
	}
}

void	pipe_commands(t_pipe *p)
{
	int		fd[2];
	t_list	*child_lst;
	pid_t	pid;
	int		i;

	i = 2;
	child_lst = NULL;
	while (i < p->ac - 1)
	{
		if (pipe(fd) == -1)
			return ;
		pid = do_fork();
		if (pid == -1)
			return (free_child_exit(&child_lst, fd));
		if (pid == 0)
			child(fd, p->av[i], p->env);
		else
		{
			parent(fd, pid, &child_lst);
			i++;
		}
	}
	wait_all_childs(child_lst);
	ft_lstclear(&child_lst, free);
}
