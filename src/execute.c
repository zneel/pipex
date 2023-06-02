/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:17:40 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/02 10:54:46 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Waits for the execution of a list of commands.
 *
 * This function waits for the execution of each command in the provided
 * linked list of commands. It uses the `waitpid` system call to wait for the
 * termination of each command's process.
 *
 * @param cmds A pointer to the linked list of commands.
 */
void	wait_for_cmds(t_list *cmds)
{
	while (cmds)
	{
		waitpid(-1, 0, 0);
		cmds = cmds->next;
	}
}

void	do_pipes(int fd[2], pid_t pid)
{
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2 child");
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("dup2 parent");
		close(fd[0]);
	}
}
/**
 * @brief Initializes a command structure and creates a child process.
 *
 * This function initializes a command structure and creates 
 * a child process using `fork()`.
 * It also creates a pipe for the command's file descriptors.
 *
 * @param cmd Pointer to the command structure to initialize.
 * @param pid Pointer to store the child process ID.
 * @return 1 on success, 0 on failure.
 */
int	pipe_fork(t_cmd *cmd, pid_t *pid, int fd[2], t_pipe *p)
{
	if (cmd->has_pipe && pipe(fd) != 0)
	{
		perror("pipe");
		return (0);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (cmd->has_pipe)
		do_pipes(fd, *pid);
	else
		dup2(p->fd2, STDOUT_FILENO);
	return (1);
}

void	execute(t_cmd *cmd, char **env)
{
	int		err;
	char	**full_cmd;

	full_cmd = get_cmd(cmd->raw_cmd, env);
	if (!full_cmd || !*full_cmd)
		return (perror("command error"));
	cmd->cmd = full_cmd;
	err = execve(cmd->cmd[0], cmd->cmd, env);
	if (err == -1)
	{
		cmd_clean(cmd);
		perror(cmd->cmd[0]);
		exit(errno);
	}
}
