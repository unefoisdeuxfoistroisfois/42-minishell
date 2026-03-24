#include "../minishell.h"

static void	pipe_child(t_cmd *command, int input_fd, int *pipe_fd)
{
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (command->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (ft_apply_redirections(command) < 0)
		exit(1);
	if (ft_is_builtin(command->args[0]))
		exit(ft_run_builtin(command));
	execvp(command->args[0], command->args);
	perror("execvp");
	exit(127);
}

static int	fork_pipeline_command(t_cmd *command, int input_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
		pipe_child(command, input_fd, pipe_fd);
	return (0);
}

int	ft_execute_pipeline(t_cmd *cmds)
{
	int		pipe_fd[2];
	int		input_fd;
	int		wait_status;
	t_cmd	*command;

	input_fd = -1;
	command = cmds;
	while (command)
	{
		if (command->next && pipe(pipe_fd) < 0)
			return (perror("pipe"), -1);
		if (fork_pipeline_command(command, input_fd, pipe_fd) < 0)
			return (-1);
		if (input_fd != -1)
			close(input_fd);
		if (command->next)
		{
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
		}
		command = command->next;
	}
	while (wait(&wait_status) > 0)
		;
	if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == 0)
		g_signal = 0;
	else
		g_signal = 1;
	return (0);
}
