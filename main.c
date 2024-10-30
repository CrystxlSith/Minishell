/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycry <crycry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:05:35 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/30 14:36:46 by crycry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
minishell> cat <s<
minishell: minishell: syntax error near unexpected token `newline'
minishell> cat <s<s
==15235== Syscall param openat(filename) contains uninitialised byte(s)
==15235==    at 0x49B7F01: open (open64.c:41)
==15235==    by 0x10ECD1: exec_redir_in (ft_redir_in_utils.c:45)
==15235==    by 0x10DC4B: exec_redirection (ft_redir_utils.c:48)
==15235==    by 0x10DBB6: fork_redirection (ft_redir_utils.c:28)
==15235==    by 0x10D74D: exec_cmd (exec_cmd_minishell.c:62)
==15235==    by 0x10D6EB: exec_cmd_minishell (exec_cmd_minishell.c:47)
==15235==    by 0x10D679: execute_fork (exec_cmd_minishell.c:34)
==15235==    by 0x10FEF7: input_execution (launch_utils.c:77)
==15235==    by 0x110012: generate_minishell_prompt (launch_utils.c:104)
==15235==    by 0x11032F: main (main.c:35)
==15235== 
==15235== Syscall param openat(filename) points to unaddressable byte(s)
==15235==    at 0x49B7F01: open (open64.c:41)
==15235==    by 0x10ECD1: exec_redir_in (ft_redir_in_utils.c:45)
==15235==    by 0x10DC4B: exec_redirection (ft_redir_utils.c:48)
==15235==    by 0x10DBB6: fork_redirection (ft_redir_utils.c:28)
==15235==    by 0x10D74D: exec_cmd (exec_cmd_minishell.c:62)
==15235==    by 0x10D6EB: exec_cmd_minishell (exec_cmd_minishell.c:47)
==15235==    by 0x10D679: execute_fork (exec_cmd_minishell.c:34)
==15235==    by 0x10FEF7: input_execution (launch_utils.c:77)
==15235==    by 0x110012: generate_minishell_prompt (launch_utils.c:104)
==15235==    by 0x11032F: main (main.c:35)
==15235==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==15235== 
infile : Bad address
exec_redir_in : Bad address
exec_redirection : Bad address
==15235== 
==15235== HEAP SUMMARY:
==15235==     in use at exit: 237,329 bytes in 331 blocks
==15235==   total heap usage: 667 allocs, 336 frees, 304,576 bytes allocated
==15235== 
==15235== LEAK SUMMARY:
==15235==    definitely lost: 32 bytes in 1 blocks
==15235==    indirectly lost: 72 bytes in 5 blocks
==15235==      possibly lost: 0 bytes in 0 blocks
==15235==    still reachable: 237,225 bytes in 325 blocks
==15235==         suppressed: 0 bytes in 0 blocks
==15235== Rerun with --leak-check=full to see details of leaked memory
==15235== 
==15235== Use --track-origins=yes to see where uninitialised values come from
==15235== For lists of detected and suppressed errors, rerun with: -s
==15235== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
==15234== 
==15234== HEAP SUMMARY:
==15234==     in use at exit: 237,329 bytes in 331 blocks
==15234==   total heap usage: 661 allocs, 330 frees, 300,088 bytes allocated
==15234== 
==15234== LEAK SUMMARY:
==15234==    definitely lost: 32 bytes in 1 blocks
==15234==    indirectly lost: 72 bytes in 5 blocks
==15234==      possibly lost: 0 bytes in 0 blocks
==15234==    still reachable: 237,225 bytes in 325 blocks
==15234==         suppressed: 0 bytes in 0 blocks
==15234== Rerun with --leak-check=full to see details of leaked memory
==15234== 
==15234== For lists of detected and suppressed errors, rerun with: -s
==15234== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==15204== Conditional jump or move depends on uninitialised value(s)
==15204==    at 0x11026C: free_token (free_utils2.c:19)
==15204==    by 0x1102C1: free_tokens (free_utils2.c:36)
==15204==    by 0x110152: free_parsed_cmd (free_utils.c:49)
==15204==    by 0x110237: free_all_line (free_utils.c:72)
==15204==    by 0x11003A: generate_minishell_prompt (launch_utils.c:107)
==15204==    by 0x11032F: main (main.c:35)
==15204== 
*/

int	g_sig_status;

int	main(int ac, char **av, char **envp)
{
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	initiate_struc_envp(&data, envp);
	tokens = NULL;
	cmd_parsing = NULL;
	(void)ac;
	(void)av;
	remove_hdc_file();
	if (generate_minishell_prompt(data, tokens, cmd_parsing) == -1)
		return (free_minishell(data), -1);
	free_minishell(data);
	return (0);
}

/*d*/
