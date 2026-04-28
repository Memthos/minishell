/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:37:25 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/28 16:58:16 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_name(t_string s, t_strings name)
{
	size_t	size;

	size = 0;
	if (s[0] == '~')
		size = 4;
	else if (ft_isalpha(s[1]) || s[1] == '_')
		while (ft_isalnum(s[size + 1]) || s[size + 1] == '_')
			size++;
	else if (s[1] == '?' || s[1] == '@' || s[1] == '*' || s[1] == '#'
		|| s[1] == '$' || s[1] == '!' || s[1] == '-' || s[1] == '_'
		|| ft_isdigit(s[1]))
		size = 1;
	else
		return (0);
	*name = malloc(sizeof(char) * (size + 1));
	if (!*name)
		return (1);
	if (s[0] == '~')
		ft_strlcpy(*name, "HOME", size + 1);
	else
		ft_strlcpy(*name, s + 1, size + 1);
	return (0);
}

t_string	get_expand_value(t_string var_name, t_shell *sh, t_status *status)
{
	t_string	value;
	t_string	tmp;

	value = NULL;
	tmp = dict_get_data(sh->env, var_name);
	if (tmp)
	{
		value = ft_strdup(tmp);
		if (!value)
		{
			*status = ALLOCATION_FAILURE;
			return (NULL);
		}
	}
	else if (!tmp && ft_strcmp(var_name, "?") == 0)
	{
		value = ft_itoa(sh->oldexitno);
		if (!value)
		{
			*status = ALLOCATION_FAILURE;
			return (NULL);
		}
	}
	return (value);
}

void	update_expanded_ast(t_ast_lst *node, t_status *status)
{
	t_lxr_lst	*lxr;
	t_ast_lst	*right;

	lxr = NULL;
	right = node->right;
	lexer(&lxr, node->data, status);
	if (!*status)
	{
		if (!lxr)
		{
			node->data = ft_calloc(1, 1);
			if (!node->data)
				*status = ALLOCATION_FAILURE;
			return ;
		}
		else
			*status = expand_to_ast(&lxr, node);
	}
	lxr_lst_clear(&lxr);
	if (!*status)
		ast_lst_last(node, RIGHT)->right = right;
	else
		ast_lst_clear(&right);
}
