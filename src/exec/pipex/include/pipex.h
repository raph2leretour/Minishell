/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:39:14 by rtissera          #+#    #+#             */
/*   Updated: 2023/06/27 09:22:44 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/************************************************/
/*   WRAPPER                                    */
/************************************************/
#ifndef PIPEX_H
# define PIPEX_H

/************************************************/
/*   INCLUDES                                   */
/************************************************/
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/include/libft.h"

/************************************************/
/*   STRUCTURES                                 */
/************************************************/

/************************************************/
/*   FUNCTIONS                                  */
/************************************************/
int		main(int ac, char **av, char **env);
char	*get_path(char *scmd, char **env);
void	error(void);
void	iwanttobreakfree(char **tofree);
void	execificator(char *cmd, char **env, int fd[2]);
void	child_process(char **av, char **env, int fd[2]);
void	parent_process(char **av, char **env, int fd[2]);

#endif
