#include "minishell.h"

char	*ft_expand_str(char *str)
{
	char	*result;
	char	*var_value;
	char	quote;
	int		i;
	int		len;

	result = ft_strdup("");
	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		if (str[i] == '$' && str[i + 1] != '\0' && quote != '\'')
		{
			len = ft_var_len(str, i + 1);
			var_value = ft_get_var_value(str, i + 1, len);
			result = ft_strjoin_free(result, var_value);
			free(var_value);
			i = i + len + 1;
		}
		else
		{
			result = ft_addchar(result, str[i]);
			i++;
		}
	}
	return (result);
}
char	*ft_get_var_value(char *str, int start, int len)
{
	char	*var_name;
	char	*value;
	char	*res;

	var_name = ft_substr(str, start, len);
	if (var_name == NULL)
	{
		return (NULL);
	}
	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		free(var_name);
		return (ft_itoa(g_exit_status));
	}
	value = getenv(var_name);
	free(var_name);
	if (value == NULL)
	{
		res = ft_strdup("");
		return (res);
	}
	res = ft_strdup(value);
	return (res);
}

int	ft_var_len(char *str, int start)
{
	int	len;
	int	bool;

	len = 0;
	// $? est un cas spécial
	if (str[start] == '?')
		return (1);
	bool = 1;
	// Variable normale : lettres, chiffres, underscore
	while (str[start + len] != '\0' && bool == 1)
	{
		if (ft_isalnum(str[start + len]) == 0 && str[start + len] != '_')
			bool = 0;
		else
			len++;
	}
	return (len);
}

int ft_is_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$')
        {
            return (1);
        }
        i ++;
    }
    return (0);
}