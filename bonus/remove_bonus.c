/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:20:48 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/13 14:20:19 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_all(int fd, int *pfd)
{
	close(fd);
	close(pfd[0]);
	close(pfd[1]);
}

int	creating_outfile(char *filename, char c, char ***cmds_args, int pfd[2])
{
	int	fd;

	fd = 0;
	if (c == 'h')
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (c == 'n')
		fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror(filename);
		epilogue(cmds_args);
		close_pipe(pfd);
		exit(1);
	}
	return (fd);
}

int	open_input_file(char *filename, char ***cmds_args, int pfd[2])
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		free_dbl_ptr(cmds_args[0], 0);
		free(cmds_args);
		close_pipe(pfd);
		exit(1);
		return (-1);
	}
	return (fd);
}

void	close_pipe(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}
