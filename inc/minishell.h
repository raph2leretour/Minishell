/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/07 16:23:23 by rtissera         ###   ########.fr       */
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
# include <signal.h>
# include "lexer.h"
# include "../libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/
int		ft_wait(pid_t last_pid);
int		create_pipe(t_command *s_cmd);
int		dupificator(t_simple_cmd *cmd);
int		is_any_redirection(t_simple_cmd *cmd);
int		execution(t_command *s_cmd, t_simple_cmd *cmd);
char	*get_key(char *env_var);
char	*get_value(char *env_var);
char	**get_true_env(t_env *s_env);
char	*ft_getenv(char *s, t_env *env);
char	**split_cmd(t_simple_cmd *cmd, bool skip);
void	pwd(void);
void	ft_env(t_env *env);
void	free_array(char **a);
void	ft_exec(t_command *t_cmd);
void	cd(char *path, t_env *env);
void	close_fds(t_simple_cmd *cmd);
void	clear_pipes(t_command *s_cmd);
void	ft_error(char *s, int errnum);
void	echo(char **array, t_env *env);
void	close_pipe(t_simple_cmd *t_cmd);
void	redirect_end(t_simple_cmd *cmd);
void	unset(t_env *env, char *targeted_token);
void	ft_exit(t_command *cmd, t_token *token);
void	do_exec(t_simple_cmd *cmd, t_env *s_env);
void	ft_export(t_command *s_cmd, t_token *token);
void	child_process(t_command *t_cmd, t_simple_cmd *cmd);
void	do_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token, int b);
t_env	*init_env_var(char *key, char *value);

#endif
