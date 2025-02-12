/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:40:21 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/11 10:36:45 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	epilogue(int fds[2], char **cmds_args[2])
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
	if (cmds_args[0])
		free_dbl_ptr(cmds_args[0], 0);
	if (cmds_args[1])
		free_dbl_ptr(cmds_args[1], 0);
}

int	check(int nth, char **argv, char **env, char **cmds_args[2])
{
	char	**tmp;
	char	*tmp1;

	if (valid_quotes(argv[2 + nth]) == 0)
		return (cmds_args[nth] = NULL, perror("Invalid quotes"), 0);
	cmds_args[nth] = ft_split(argv[2 + nth], ' ');
	if (cmds_args[nth][0] == NULL)
		return (perror("' ' is not a command"), 0);
	tmp = cmds_args[nth];
	tmp1 = cmds_args[nth][0];
	cmds_args[nth][0] = check_commands(env, cmds_args[nth][0]);
	if (cmds_args[nth][0] == NULL)
	{
		tmp[0] = tmp1;
		return (free_dbl_ptr(tmp, 0), cmds_args[nth] = NULL, 0);
	}
	free(tmp1);
	return (1);
}

void	execute(int fds[2], int pfd[2], char **cmds_args[2], int nth)
{
	if (nth == 0)
	{
		if (fork() == 0)
		{
			dup2(fds[0], 0);
			dup2(pfd[1], 1);
			close_all(fds, pfd);
			execve(cmds_args[0][0], cmds_args[0], NULL);
			return (epilogue(fds, cmds_args), exit(1));
		}
	}
	else if (nth == 1)
	{
		if (fork() == 0)
		{
			dup2(pfd[0], 0);
			dup2(fds[1], 1);
			close_all(fds, pfd);
			close(fds[1]);
			execve(cmds_args[1][0], cmds_args[1], NULL);
			return (epilogue(fds, cmds_args), exit(1));
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fds[2];
	char	**cmds_args[2];
	int		status;
	int		pfd[2];

	cmds_args[0] = NULL;
	cmds_args[1] = NULL;
	check_files(argc, argv, fds);
	pipe(pfd);
	if (check(0, argv, env, cmds_args) != 0)
		execute(fds, pfd, cmds_args, 0);
	close(fds[0]);
	close(pfd[1]);
	fds[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fds[1] == -1)
		return (perror(argv[argc - 1]),
			epilogue(fds, cmds_args), exit(1), 0);
	if (check(1, argv, env, cmds_args) != 0)
		execute(fds, pfd, cmds_args, 1);
	close(pfd[0]);
	close(pfd[1]);
	while (wait(&status) >= 0)
		continue ;
	return (epilogue(fds, cmds_args), 0);
}
