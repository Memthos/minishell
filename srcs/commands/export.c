#include "../../includes/minishell.h"

t_status	export(t_dictionary **env_dict, char *name, char *value, bool concatenate)
{
	char			*tmp;
	t_dictionary	*entry;

	if (NULL == name && NULL != value)
		return (FAILURE);
	if (NULL == name && NULL == value)
	{
		env(env_dict);
		return (SUCCESS);
	}
	entry = dict_get(*env_dict, name);
	if (NULL == entry)
	{
		if (NULL == dict_add(env_dict, name, value))
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
