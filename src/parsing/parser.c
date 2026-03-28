#include "minishell.h"

t_cmd	*ft_parser(t_list *list)
{
	t_cmd	*first;
	t_cmd	*cmd;
	t_cmd	*prev;
	t_token	*token;

	first = NULL;
	prev = NULL;
	while (list != NULL)
	{
		cmd = ft_parse_cmd(&list);
		if (first == NULL)
			first = cmd;
		if (prev != NULL)
			prev->next = cmd;
		prev = cmd;
		if (list != NULL)
		{
			token = (t_token *)list->content;
			if (token->type == PIPE)
				list = list->next;
		}
	}
	return (first);
}

t_cmd	*ft_parse_cmd(t_list **list)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = ft_create_cmd();
	if (cmd == NULL)
		return (NULL);
	while (*list != NULL)
	{
		token = (t_token *)(*list)->content;
		if (token->type == PIPE)
			return (cmd);
		else if (token->type >= REDIR_IN && token->type <= APPEND)
			ft_redir(cmd, list);
		else if (token->type == WORD)
		{
			cmd->args = ft_add_word(cmd->args, token->value);
			*list = (*list)->next;
		}
		else
			*list = (*list)->next;
	}
	return (cmd);
}

t_cmd	*ft_create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->delimiter = NULL;
	cmd->next = NULL;
	return (cmd);
}
