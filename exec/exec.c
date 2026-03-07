#include "../minishell.h"
#include <fcntl.h>

static int	ft_redirect_input(t_cmd *cmd)
{
	// Redirige stdin vers le fichier d'entrée
	int	fd;

	fd = open(cmd->input_file, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->input_file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	ft_redirect_output(t_cmd *cmd)
{
	// Redirige stdout vers le fichier de sortie, avec ajout si spécifié
	int	fd;

	if (cmd->append)
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror(cmd->output_file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	ft_apply_redirections(t_cmd *cmd)
{
	// Applique les redirections d'entrée et de sortie pour la commande
	if (cmd->input_file && ft_redirect_input(cmd) < 0)
		return (-1);
	if (cmd->output_file && ft_redirect_output(cmd) < 0)
		return (-1);
	return (0);
}
static void	ft_execute_child(t_cmd *cmd)
{
	// Exécute la commande dans le processus enfant après application des redirections
	if (ft_apply_redirections(cmd) < 0)
		exit(1);
	execvp(cmd->args[0], cmd->args);
	perror("execvp");
	exit(127);
}

int	ft_execute_simple_cmd(t_cmd *cmd)
{
	// Fork et exécute une commande simple, en attendant la fin
	pid_t	pid;
	int		stat;

	if (!cmd || !cmd->args[0])
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		ft_execute_child(cmd);
	}
	if (waitpid(pid, &stat, 0) < 0)
	{
		perror("waitpid");
		return (-1);
	}
	return (0);
}

int	ft_execute(t_cmd *cmds)
{
	// Exécute une liste de commandes de manière séquentielle
	t_cmd	*lst;
	int		ret;

	if (!cmds)
		return (0);
	lst = cmds;
	ret = 0;
	while (lst)
	{
		ret = ft_execute_simple_cmd(lst);
		lst = lst->next;
	}
	return (ret);
}
