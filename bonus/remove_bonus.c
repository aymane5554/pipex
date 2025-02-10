/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:20:48 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/10 11:37:33 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	remove_element(char	***cmds_args, int index)
{
	int		i;
	char	**tmp;

	i = index;
	while (cmds_args[i + 1])
	{
		tmp = cmds_args[i];
		cmds_args[i] = cmds_args[i + 1];
		cmds_args[i + 1] = tmp;
		i++;
	}
}

void	close_all(int *fds, int *pfd)
{
	close(fds[0]);
	close(pfd[0]);
	close(pfd[1]);
}

void	creating_outfile(int fds[2], char **argv, int argc)
{
	if (fds[1] == 0)
		fds[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (fds[1] == 1)
		fds[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
}
