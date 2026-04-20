/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:17:30 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/20 20:43:07 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	export_display_env(t_shell *shell);
t_status	export_special_case(t_strings *args);
t_strings	export_set_entry(t_strings *args, t_shell *shell);
t_status	export_check_entry(t_strings *entry, t_strings *args, bool *cat);
t_status	export_update_env(t_strings *entry, t_shell *shell, bool concat);

t_status	cmd_export(t_strings args, t_shell *shell)
{
	t_status		code;
	t_strings		entry;
	bool			concat;

	if (NULL == *(++args))
		return (export_display_env(shell));
	code = SUCCESS;
	while (*args)
	{
		code = export_special_case(&args);
		if (SUCCESS != code)
			continue ;
		entry = export_set_entry(&args, shell);
		if (NULL == entry)
		{
			code = FAILURE;
			continue ;
		}
		code = export_check_entry(&entry, &args, &concat);
		if (SUCCESS != code)
			continue ;
		export_update_env(&entry, shell, concat);
		++args;
	}
	return (code);
}
