/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:57:10 by smilosav          #+#    #+#             */
/*   Updated: 2024/01/19 20:20:40 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define COMMAND 1
# define ARGUMENT 2
# define REDIRECTION 3
# define PIPE 4
# define SEMI 5
# define AND 6
# define OPTION 7

extern int			g_status;

typedef struct s_token
{
	char				*str;
	int					type;
	struct s_token		*prev;
	struct s_token		*next;
}					t_token;

typedef struct s_simple_cmd
{
	char				*full_path;
	int					infile;
	int					outfile;
	int					in;
	int					out;
	struct s_token		*first_token;
	struct s_simple_cmd	*prev;
	struct s_simple_cmd	*next;
}					t_simple_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_command
{
	int					flag_s;
	int					flag_d;
	char				*string;
	struct s_token		*first_token;
	struct s_simple_cmd	*first_cmd;
	struct s_env		*lst_env;
}						t_command;

t_command			*tokenize(char *command, t_env *env);
t_token				*init_token(char *value, int type);
t_token				*token_last(t_token *lst);
t_simple_cmd		*cmd_last(t_simple_cmd *lst);
t_env				*get_env_vars(char **envp);

void				add_token(t_token **lst, t_token *new_token);
void				add_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new_cmd);
void				add_env_var(t_env **lst, t_env *new_env);
void				free_cmd(t_command *cmd);
void				free_split(char **str);
void				free_env_vars(t_env *env_var);
void				var_not_double_quoted(char *str);
void				check_if_builtin(t_command *cmd_struct);
void				go_through_simple_cmds(t_simple_cmd *simple_cmd);
void				delete_invalid_var(t_token *token, int i);
void				expand_var(t_token *token, int i, t_env *env_var);
void				signals(void);
char				*get_cmd_path(char *cmd, t_command *cmd_struct);

int					add_token_word(t_command *cmd_struct, int i);
int					add_token_redirection(t_command *cmd_struct, int i);
int					add_token_parenthesis(t_command *cmd_struct, int i);
int					add_token_pipe(t_command *cmd_struct, int i);
int					add_token_and(t_command *cmd_struct, int i);
int					add_token_semi(t_command *cmd_struct, int i);
int					is_space(char c);
int					is_parenthesis(char c);
int					is_redirection(char c);
int					is_word(char c);
int					is_builtin(char *str);
int					redirect_output(char *file, int old_fd,
						t_command *cmd_struct);
int					redirect_input(char *file, int old_fd,
						t_command *cmd_struct);
int					redirect_append(char *file, int old_fd,
						t_command *cmd_struct);
int					check_options(t_command *cmd_struct);
int					is_absolute_path(char *cmd);
int					cmd_contains_builtin(t_simple_cmd *simple_cmd);
int					check_quotes(t_command *cmd_struct);
int					change_flag(int flag);
int					check_redirections(t_command *cmd_struct);
int					check_between_pipes(t_command *cmd_struct);
int					check_syntax(t_command *cmd_struct);
int					expanding(t_command *cmd_struct);
int					handle_redirections(t_command *cmd_struct);
int					set_simple_commands(t_command *cmd_struct);
int					delete_quotes(t_command *cmd);
int					check_quoted_dollar(int i, t_token *token, t_env *env_var);
int					is_name(char c);
int					check_form1(char *token_substr, char *valid_var,
						char *token, int i);
int					check_form2(char *token_substr,
						char *valid_var, char *token);
int					contains_invalid_dollar(t_token *token,
						int i, t_env *env_var);
int					get_len(char *token, int i);
int					contains_valid_var(char *token, int i, t_env *env_var);
int					wrong_var_form(char *token, int i, char *key);
int					expand_quoted(int i, t_token *token, t_env *env_var);
int					dollar_quoted(char *token, int i);
int					no_more_quotes(char *str, int i);
int					heredoc(t_command *cmd_struct);
int					handle_backslash(t_command *cmd);
int					check_executables(t_command *cmd);
int					set_option_type(t_simple_cmd *simple_cmd);

#endif
