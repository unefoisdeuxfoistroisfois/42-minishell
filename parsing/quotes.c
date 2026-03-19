#include "minishell.h"

int	ft_check_quotes(char *str)
{
	char  quote;
	int i;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
    {
			quote = str[i];
    }
		else if (str[i] == quote)
    {
			quote = 0;
    }
		i++;
	}
	if (quote != 0)
  {
		return (1);
  }
	return (0);
}

char  *ft_remove_quotes(char *str)
{
	char  *result;
	char  quote;
	int i;
	int j;

	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (result == NULL)
  {
    return (NULL);
  }
	quote = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
    {
			quote = str[i];
    }
		else if (str[i] == quote)
    {
			quote = 0;
    }
		else
    {
      result[j++] = str[i];
    }
		i++;
	}
	result[j] = '\0';
  return (result);
}
