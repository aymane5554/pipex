/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:30:34 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/01 09:49:41 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

void	check_argc(int argc);
char	*get_input(char	**argv);
void	execute3(int pfd[2], char ***cmds_args, char **argv);
int		cmds_number(char ***cmds_args);
void	allocate(char ****cmds_args, char is_here, int argc, char **argv);
void	check_files(int argc, char **argv);
int		find_path_var(char **env);
char	*check_commands(char **env, char *cmd);
void	free_dbl_ptr(char **ptr, int i);
int		valid_quotes(char	*str);
void	free_trpl_ptr(char ***ptr, int i);
void	wait_for_all(void);
void	close_all(int fd, int *pfd);
int		creating_outfile(char *filename,
			char c, char ***cmds_args, int pfd[2]);
void	epilogue(char ***cmds_args);
void	close_pipe(int pfd[2]);
int		open_input_file(char *filename, char ***cmds_args, int pfd[2]);
#endif
