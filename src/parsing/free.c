#include "minishell.h"

static void	ft_free_args(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	ft_free_cmd_fields(t_cmd *cmd)
{
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->delimiter)
		free(cmd->delimiter);
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		ft_free_args(cmd->args);
		ft_free_cmd_fields(cmd);
		free(cmd);
		cmd = tmp;
	}
}

static void	ft_free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	ft_free_tokens(t_list *list)
{
	t_list	*tmp;
	t_token	*token;

	while (list)
	{
		tmp = list->next;
		token = (t_token *)list->content;
		ft_free_token(token);
		free(list);
		list = tmp;
	}
}
