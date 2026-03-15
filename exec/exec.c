#include "../minishell.h"
#include <fcntl.h>

static int	ft_redirect_input(t_cmd *command)
{
	// Redirige stdin vers le fichier d'entrée
	int	fd;

	fd = open(command->input_file, O_RDONLY);
	if (fd < 0)
	{
		perror(command->input_file);
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

static int	ft_redirect_output(t_cmd *command)
{
	// Redirige stdout vers le fichier de sortie, avec ajout si spécifié
	int	fd;

	if (command->append)
		fd = open(command->output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(command->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror(command->output_file);
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

int	ft_apply_redirections(t_cmd *command)
{
	// Applique les redirections d'entrée et de sortie pour la commande
	if (command->input_file && ft_redirect_input(command) < 0)
		return (-1);
	if (command->output_file && ft_redirect_output(command) < 0)
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

int	ft_execute_simple_cmd(t_cmd *command)
{
	// Fork et exécute une commande simple, en attendant la fin
	pid_t	pid;
	int		stat;

	if (!command || !command->args[0])
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		ft_execute_child(command);
	}
	if (waitpid(pid, &stat, 0) < 0)
	{
		perror("waitpid");
		return (-1);
	}
	if (stat == 0)
		g_signal = 0;
	else
		g_signal = 1;
	return (0);
}

int	ft_execute(t_cmd *commands)
{
	if (!commands)
		return (0);
	if (commands->next)
		return (ft_execute_pipeline(commands));
	return (ft_execute_simple_cmd(commands));
}
