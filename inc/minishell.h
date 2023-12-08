/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/08 17:07:23 by rtissera         ###   ########.fr       */
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
# include "../libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/
typedef struct s_env
{
	bool			e;
	char			*value;
	struct s_env	*next;
}	t_env;

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/
int		ft_exit(char *strn, t_env *env);
int		pipex(int argc, char **argv, char **envp);
char	*get_path(char *scmd, char **env);
void	pwd(void);
void	cd(char *array);
void	ft_env(t_env *env);
void	echo(char **array);
void	clear_env(t_env *env);
void	unset(char *name, t_env *env);
void	iwanttobreakfree(char **tofree);
void	ft_export(char *value, t_env *env);
void	ft_error(const char *s, int errnum);
void	execificator(char *cmd, char **env, int fd[2]);
void	child_process(char **argv, char **envp, int fd[2]);
void	parent_process(char **argv, char **envp, int fd[2]);
t_env	*env_init(char **env);

#endif
