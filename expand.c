#include "minishell.h"

/*
** Expand only `$?` using the only global variable:
** g_signal == 0 => "0", else => "1"
*/
char	*ft_expand_vars(const char *s)
{
	char	*out;
	char	*tmp;
	char	*status;
	int		i;

	if (!s)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{

			if (g_signal == SIGINT)
				status = "130";
			else if (g_signal == SIGQUIT)
				status = "131";
			else if (g_signal == 0)
				status = "0";
			else
				status = "1";
			tmp = ft_strjoin(out, status);
			free(out);
			out = tmp;
			i += 2;
		}
		else
		{
			status = ft_substr(s, i, 1);
			tmp = ft_strjoin(out, status);
			free(status);
			free(out);
			out = tmp;
			i++;
		}
	}
	return (out);
}
