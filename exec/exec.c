#include "../minishell.h"
#include <fcntl.h>
#include <errno.h>

static int	open_input_file(t_cmd *command)
{
	int	fd;

	fd = open(command->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(command->infile);
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

static int	open_output_file(t_cmd *command)
{
	int	fd;

	if (command->append)
		fd = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror(command->outfile);
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
	if (command->infile && open_input_file(command) < 0)
		return (-1);
	if (command->outfile && open_output_file(command) < 0)
		return (-1);
	return (0);
}

static int	simple_command_runner(t_cmd *command)
{
	pid_t	pid;
	int		status;

	if (!command || !command->args || !command->args[0])
		return (0);
	if (ft_is_builtin(command->args[0]))
	{
		if (ft_apply_redirections(command) < 0)
			return (1);
		status = ft_run_builtin(command);
		g_signal = (status == 0);
		return (status);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		if (ft_apply_redirections(command) < 0)
			exit(1);
		execvp(command->args[0], command->args);
		perror("execvp");
		exit(127);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), -1);
	g_signal = (WIFEXITED(status) && WEXITSTATUS(status) == 0) ? 0 : 1;
	return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}

int	ft_execute(t_cmd *commands)
{
	if (!commands)
		return (0);
	if (commands->next)
		return (ft_execute_pipeline(commands));
	return (simple_command_runner(commands));
}
