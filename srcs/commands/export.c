#include "../../includes/minishell.h"

t_status	export(t_dictionary **env, char *name, char *value, bool concatenate)
{
	char			*tmp;
	t_dictionary	*entry;

	if (NULL == env || NULL == name)
		return (FAILURE);
	entry = dict_get(*env, name);
	if (NULL == entry)
	{
		if (NULL == dict_add(env, name, value))
			return (FAILURE);
		return (SUCCESS);
	}
	if (concatenate)
	{
		tmp = ft_strjoin((char *)entry->data, value);
		if (NULL == tmp)
			return (FAILURE);
		free(entry->data);
		entry->data = tmp;
		return (FAILURE);
	}
	free(entry->data);
	entry->data = value;
	return (SUCCESS);
}
