#include "minishell.h"

int	ft_execute(t_cmd *cmds)
{
	if (!cmds)
		return (0);
	if (cmds->next)
		return (ft_exec_pipeline(cmds));
	return (ft_exec_simple(cmds));
}
