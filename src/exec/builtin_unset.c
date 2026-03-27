#include "minishell.h"

int	ft_builtin_unset(t_cmd *cmd)
{
	(void)cmd;
	/* TODO: Implémenter la suppression de variables
	** Sans unsetenv, il faut:
	** 1. Trouver la variable dans environ
	** 2. Décaler toutes les variables suivantes
	*/
	return (0);
}
