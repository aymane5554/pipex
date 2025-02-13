/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:46:08 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/13 11:59:14 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

int	open_input_file(char *filename, char **cmds_args[2], int pfd[2])
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		epilogue(cmds_args);
		close_pipe(pfd);
		exit(1);
		return (-1);
	}
	return (fd);
}

int	open_output_file(char *filename, char **cmds_args[2], int pfd[2])
{
	int	fd;

	if (access(filename, F_OK) == 0)
	{
		if (access(filename, W_OK) == -1)
		{
			perror(filename);
			epilogue(cmds_args);
			close_pipe(pfd);
			exit(1);
			return (-1);
		}
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (perror(filename),
			epilogue(cmds_args), exit(1), -1);
	return (fd);
}
