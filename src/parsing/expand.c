#include "minishell.h"

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