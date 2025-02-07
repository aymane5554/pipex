/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:20:48 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/07 15:45:52 by ayel-arr         ###   ########.fr       */
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
	close(fds[1]);
	close(pfd[0]);
	close(pfd[1]);
}

char	**garbage(void)
{
	char	**garbage_value;

	garbage_value = malloc(sizeof(char *));
	*garbage_value = ft_strdup("#");
	return (garbage_value);
}
