/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:41:37 by ebouvier          #+#    #+#             */
/*   Updated: 2023/05/29 22:00:14 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_pipe *px)
{
	free(px->file1);
	free(px->file2);
	if (px->cmds)
		ft_lstclear(&px->cmds, free);
}
void print_usage()
{
    ft_printf("usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
}

void	check_args(int ac)
{
	if (ac < 5)
    {
        print_usage();
		exit(0);
    }
}

int	main(int ac, char **av)
{
	t_pipe	px;
	t_list	*new_node;
	char	*tmp;
	int		i;

	check_args(ac);
	px.file1 = ft_strdup(av[1]);
	px.file2 = ft_strdup(av[ac - 1]);
	px.cmds = NULL;
	i = 2;
	while (i < ac - 1)
	{
		tmp = ft_strdup(av[i]);
		if (!tmp)
			return (free_all(&px), exit(1), 0);
		new_node = ft_lstnew(tmp);
		if (!new_node)
			return (free_all(&px), exit(1), 0);
		ft_lstadd_back(&px.cmds, new_node);
		i++;
	}
	ft_printf("file1=%s\n", px.file1);
	ft_printf("file2=%s\n", px.file2);
	ft_lstprint_str(px.cmds);
	free_all(&px);
	return (0);
}
