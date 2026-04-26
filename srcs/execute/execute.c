/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/26 16:04:12 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	execute_word(t_ast_lst *cmd, t_shell *shell);
t_status	execute_pipe(t_ast_lst *cmd, t_shell *shell);
t_status	execute_out_redirection(t_ast_lst *cmd, t_shell *shell);
t_status	execute_in_redirection(t_ast_lst *cmd, t_shell *shell);
t_status	execute_heredoc(t_ast_lst *cmd, t_shell *shell);
t_status	execute_cmd_list(t_ast_lst *cmd, t_shell *shell);
t_status	execute_parentheses(t_ast_lst *cmd, t_shell *shell);

t_status	execute(t_ast_lst *cmd, t_shell *shell)
{
	if (NULL == cmd)
		return (shell->exitno);
	if (WORD == cmd->token || WILDCARD == cmd->token)
		return (execute_word(cmd, shell));
	if (PIPE == cmd->token)
		return (execute_pipe(cmd, shell));
	if (GREAT == cmd->token || DGREAT == cmd->token)
		return (execute_out_redirection(cmd, shell));
	if (LESS == cmd->token)
		return (execute_in_redirection(cmd, shell));
	if (DLESS == cmd->token)
		return (execute_heredoc(cmd, shell));
	if (AND_IF == cmd->token || OR_IF == cmd->token)
		return (execute_cmd_list(cmd, shell));
	if (CMP_CMD == cmd->token)
		return (execute_parentheses(cmd, shell));
	return (shell->exitno);
}
