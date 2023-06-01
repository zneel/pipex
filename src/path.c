/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:42:07 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 11:03:47 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	test_cmd(char *cmd)
{
	return (access(cmd, F_OK | X_OK) == 0);
}

char	**split_paths(char *env)
{
	char	**paths;

	paths = ft_split(env, ":");
	if (!paths || !*paths)
		return (NULL);
	return (paths);
}

char	*get_good_cmd(char **paths, char *cmd)
{
	char	*good_cmd;
	char	*good_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		good_path = ft_strjoin(paths[i], "/");
		good_cmd = ft_strjoin(good_path, cmd);
		free(good_path);
		if (test_cmd(good_cmd))
			return (good_cmd);
		free(good_cmd);
		i++;
	}
	return (NULL);
}

char	*join_cmd(char *cmd, char **env)
{
	char	**paths;
	int		i;
	char	*good_cmd;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			paths = split_paths(env[i]);
			if (!paths)
				return (NULL);
			good_cmd = get_good_cmd(paths, cmd);
			if (good_cmd)
				return (free_split(paths), good_cmd);
		}
		i++;
	}
	return (NULL);
}

char	**get_cmd(char *full_cmd, char **env)
{
	char	**cmd;
	char	*pathed_cmd;

	cmd = ft_split(full_cmd, " ");
	if (!cmd || !*cmd)
		return (NULL);
	if (test_cmd(cmd[0]))
		return (cmd);
	if (!env || !*env)
		return (free_split(cmd), NULL);
	pathed_cmd = join_cmd(cmd[0], env);
	if (!pathed_cmd)
	{
		perror("command error");
		free_split(cmd);
		return (NULL);
	}
	free(cmd[0]);
	cmd[0] = pathed_cmd;
	return (cmd);
}
