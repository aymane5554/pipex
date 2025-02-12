/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:25:36 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/10 11:42:52 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	cmp(char *line, char *limiter)
{
	int	i;

	i = 0;
	if (limiter[0] != '\0' && line[0] == '\n')
		return (1);
	while (line[i] != '\n' || limiter[i] != '\0')
	{
		if (line[i] != limiter[i])
			return (1);
		i++;
	}
	return (0);
}

char	*get_input(char	**argv)
{
	char	*line;
	char	*input;
	char	*tmp;
	char	*tmp2;

	input = NULL;
	line = get_next_line(0);
	while (cmp(line, argv[2]) != 0)
	{
		tmp = line;
		tmp2 = input;
		input = ft_strjoin(input, line);
		free(tmp2);
		free(tmp);
		line = get_next_line(0);
	}
	free(line);
	return (input);
}

void	execute3(int fds[2], int pfd[2], char ***cmds_args, char **argv)
{
	int		pfd2[2];
	char	*input;

	input = get_input(argv);
	pipe(pfd2);
	if (input)
		write(pfd2[1], input, ft_strlen(input));
	free(input);
	get_next_line(-1);
	close(pfd2[1]);
	if (fork() == 0)
	{
		dup2(pfd2[0], 0);
		dup2(pfd[1], 1);
		close_all(fds, pfd);
		close(pfd2[0]);
		close(pfd2[1]);
		execve(cmds_args[0][0], cmds_args[0], NULL);
		epilogue(fds, cmds_args);
		exit(1);
	}
	close(pfd2[0]);
}

void	check_argc(int argc)
{
	if (argc == 1)
	{
		perror("\e[31mThe program should be executed as follows:\n"
			"\t./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
}

void	wait_for_all(void)
{
	int	status;

	while (wait(&status) >= 0)
		continue ;
}
