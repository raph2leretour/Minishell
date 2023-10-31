/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:57:10 by smilosav          #+#    #+#             */
/*   Updated: 2023/10/31 20:36:15 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type
{
	EMPTY,
	ARG,
	CMD,
	INPUT, //<
	OUTPUT, //>
	APPEND, //>>
	HERE_DOC, //<<
	PIPE,
	END
}				t_token_type;

typedef	struct			s_token
{
	char		*str;
	t_token_type	type;
	//bool		expanded;
	struct s_token		*prev;
	struct s_token		*next;
}				t_token;

typedef	struct				s_command
{
	char			*string;
	char			**argv;
	struct s_token			*first_token;
	struct s_command		*next;
}					t_command;

char	**tokenize(char *command);
#endif
