/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/20 19:54:08 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*   INCLUDES                                                                 */
/******************************************************************************/
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "lexer.h"
# include "../libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/
int		create_pipe(t_command *s_cmd);
int		execution(t_command *s_cmd, t_simple_cmd *cmd);
char	**get_true_env(t_env *s_env);
char	**split_cmd(t_simple_cmd *cmd);
void	pwd(void);
void	cd(char *array);
void	ft_env(t_env *env);
void	echo(char **array);
void	ft_exit(char *strn);
void	ft_exec(t_command *t_cmd);
void	clear_pipes(t_command *s_cmd);
void	ft_error(const char *s, int errnum);
void	unset(t_env *env, char *targeted_token);
void	ft_export(t_command *s_cmd, t_token *token);
void	do_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token);

#endif
