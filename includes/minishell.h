/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:06:23 by agiliber          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/10/18 11:24:12 by agiliber         ###   ########.fr       */
=======
/*   Updated: 2024/10/21 13:17:20 by agiliber         ###   ########.fr       */
>>>>>>> Minishell_AGT
=======
/*   Updated: 2024/10/21 15:12:13 by jopfeiff         ###   ########.fr       */
>>>>>>> 0f2fb0de3936a87fb5364b63e3d089244d360d71
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"

# include "../libft/libft.h"
# include "parsing.h"
# include "builtins.h"
# include "pipex.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <dirent.h>

# define TRUE 1
# define FALSE 0

extern int	g_sig_status;

typedef struct s_minishell
{
	char	*line_read;
	int		i;
}			t_minishell;

//LEXER && PARSER
int		ft_exit_shell(t_cmd *cmd_parsing, t_env *data, t_lexer *tokens);
t_lexer	*tokenize(char *str);
void	create_new_token(t_lexer_type type, char *data, t_lexer **tokens);
void	new_token(t_lexer **tokens, t_lexer *new_node);

//BUILTINS ---> GENERAL
int		builtins(t_cmd **parsing, t_env **data);

//ft_print_utils
void	print_cmd(t_cmd *head);
void	print_tokens(t_lexer *tokens);
void	print_heredoc(t_heredoc *hdc);

//ft_launch_utils
int		launcher_exec(char *input, t_env **data, t_cmd **parsing, \
	t_minishell *mini);
int		start_error(char *input);
<<<<<<< HEAD
void	input_execution(t_env *data, t_cmd *cmd_parsing, t_minishell minishell);
=======
void	input_execution(t_env *data, t_cmd *cmd_parsing, \
	t_minishell *minishell);
>>>>>>> Minishell_AGT
int		generate_minishell_prompt(t_env *data, t_lexer *tokens, \
	t_cmd *cmd_parsing);

//free_utils
void	free_token(t_lexer *token);
void	free_tokens(t_lexer *tokens);
void	free_parsed_cmd(t_cmd *head);
void	free_minishell(t_env **data, t_cmd **parsing, t_minishell *minishell);
void	free_all_line(t_lexer *tokens, t_cmd *cmd_parsing);

//Heredocs
int		initiate_hdc_struc(t_cmd **parsing);
int		ft_remove(const char *pathname);
int		open_heredoc_file(int flags);
void	write_to_heredoc(int fd, char *line);
void	handle_heredoc(t_cmd **cmd_parsing, t_env **data, t_minishell *mini);
<<<<<<< HEAD
int		launcher_exec(char *input, t_env **data, t_cmd **parsing, \
	t_minishell *minishell);
=======
>>>>>>> Minishell_AGT
void	heredoc(t_cmd *cmd_parsing, t_env **data, t_minishell *mini);
void	print_hdc_error(char *token , char *token2);

#endif