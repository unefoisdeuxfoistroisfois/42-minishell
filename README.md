*This project has been created as part of the 42 curriculum by britela-, ouamarko.*

# minibiendur 🐚

## Description

Minishell is a minimal Unix shell written in C, built as part of the 42 curriculum. The goal is to reproduce a subset of Bash's behavior — prompt display, command execution, piping, redirections, environment variable expansion, signal handling, and a set of built-in commands.

The project is split between two parts: **britela-** handled parsing (lexer, token expansion, quote handling, syntax checking, parser) and **ouamarko** handled execution (pipelines, redirections, heredoc, builtins, path resolution).

## Instructions

### Requirements

- `cc`, `make`, `readline` library

On Debian/Ubuntu:
```bash
sudo apt install libreadline-dev
```

On macOS (with Homebrew):
```bash
brew install readline
```

### Compilation

```bash
make
```

### Usage

```bash
./minishell
```

The shell will display a `minibiendur$` prompt. Type any command and press Enter.

### Supported features

- Command execution via `PATH`, relative path, or absolute path
- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion: `$VAR`, `$?`
- Single and double quote handling
- Command history (up/down arrows)
- Signal handling: `ctrl-C`, `ctrl-D`, `ctrl-\`

### Built-in commands

| Command | Description |
|---------|-------------|
| `echo [-n]` | Print arguments to stdout |
| `cd [path]` | Change working directory |
| `pwd` | Print current directory |
| `export [var=val]` | Set or display environment variables |
| `unset [var]` | Remove environment variables |
| `env` | Print all environment variables |
| `exit [code]` | Exit the shell |

### Cleanup

```bash
make clean   # remove object files
make fclean  # remove object files and binary
make re      # full recompile
```

## Resources

### Documentation & references

- [Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html) — used as the main behavioral reference
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — for prompt and history
- `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid` — core syscalls
- `man 7 signal`, `man 3 sigaction` — signal handling
- [Writing Your Own Shell](https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html) — general guidance on shell architecture

### AI usage

AI (Claude) was used to get explanations on how pipes work internally (`fork`, `dup2`, `execve` chaining) as a learning resource. Google Search was also used for debugging and tracking down memory leaks — looking up man pages, Stack Overflow threads, and community discussions.
