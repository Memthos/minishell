/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:17:30 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/23 11:12:30 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	export_display_env(t_shell *shell);
t_status	export_special_case(t_strings *args);
t_strings	export_set_entry(t_strings *args);
t_status	export_check_entry(t_strings *entry, t_strings *args, bool *cat);
t_status	export_update_env(t_strings *entry, t_shell *shell, bool concat);

static t_status	export_logic(t_strings *args, t_shell *shell)
{
	bool		concat;
	t_strings	entry;

	if (SUCCESS != export_special_case(args))
		return (FAILURE);
	entry = export_set_entry(args);
	if (NULL == entry)
		return (FAILURE);
	if (SUCCESS != export_check_entry(&entry, args, &concat))
		return (FAILURE);
	if (SUCCESS != export_update_env(&entry, shell, concat))
		return (FAILURE);
	return (SUCCESS);
}

t_status	cmd_export(t_strings args, t_shell *shell)
{
	t_status	code;

	if (NULL == *(++args))
		return (export_display_env(shell));
	code = SUCCESS;
	while (*args)
	{
		if (SUCCESS != export_logic(&args, shell))
		{
			code = FAILURE;
			continue ;
		}
		++args;
	}
	return (code);
}
