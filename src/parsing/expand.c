#include "minishell.h"

void	ft_update_quote(char c, char *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

char	*ft_expand_var(char *str, int *i, char *result)
{
	char	*var_value;
	int		len;

	len = ft_var_len(str, *i + 1);
	var_value = ft_get_var_value(str, *i + 1, len);
	result = ft_strjoin_free(result, var_value);
	free(var_value);
	*i = *i + len + 1;
	return (result);
}

char	*ft_expand_str(char *str)
{
	char	*result;
	char	quote;
	int		i;

	result = ft_strdup("");
	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ft_update_quote(str[i], &quote);
		if (str[i] == '$' && str[i + 1] != '\0' && quote != '\'')
			result = ft_expand_var(str, &i, result);
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

	var_name = ft_substr(str, start, len);
	if (var_name == NULL)
		return (NULL);
	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		free(var_name);
		return (ft_itoa(g_exit_status));
	}
	value = getenv(var_name);
	free(var_name);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	ft_var_len(char *str, int start)
{
	int	len;

	len = 0;
	if (str[start] == '?')
		return (1);
	while (str[start + len] != '\0')
	{
		if (ft_isalnum(str[start + len]) == 0 && str[start + len] != '_')
			break ;
		len++;
	}
	return (len);
}
