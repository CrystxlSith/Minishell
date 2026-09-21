# Minishell

A small Unix shell in C modeled on bash. 42 school project, built as a pair (2024).

## Features

- Interactive prompt with history (GNU readline).
- Three-stage pipeline:
  - **lexer**: splits the line into typed tokens (words, quotes, pipes, redirections) and reports syntax errors;
  - **parser**: builds one command per pipeline segment, with its arguments, redirections and heredocs, and expands variables;
  - **executor**: forks and runs each command with `execve`, looking it up in `PATH`. A builtin alone on its line runs in the shell process.
- Quotes: single quotes are literal, double quotes expand variables.
- Expansion of `$VAR` and `$?`.
- Pipelines of any length.
- Redirections `<`, `>`, `>>` and heredocs `<<`, read in a child process, with several heredocs per command.
- Builtins: `echo` (with `-n`), `cd` (with `~` and `-`, updates `PWD` and `OLDPWD`), `pwd`, `export`, `unset`, `env`, `exit`.
- Exit status in `$?`: 127 for an unknown command, 2 for a syntax error.
- Signals: `Ctrl-C` shows a fresh prompt, `Ctrl-D` exits, `Ctrl-\` is ignored at the prompt. A single global variable stores the received signal.
- Syntax errors: unclosed quotes, pipe at the start, at the end or doubled, redirection without a target.

The bonus part (`&&`, `||`, parentheses, `*` wildcards) is not implemented.

## Build and run

Requirements: `cc`, `make` and GNU readline (`sudo apt install libreadline-dev`).

```sh
git clone https://github.com/CrystxlSith/Minishell.git
cd Minishell
make
./minishell
```

`./run.sh` starts the shell under Valgrind (leaks and file descriptors), with `readline.supp` hiding readline's own allocations.

## Project structure

```
main.c
src/lexer/         tokenizer and syntax errors
src/parser/        command list, variable expansion, signals
src/redirections/  execution, pipes, redirections, heredocs, PATH lookup
src/builtins/      echo, cd, pwd, export, unset, env, exit
src/helper/        main loop and cleanup
libft/             our libft
```

## Team

Armel ([@Canybardeloton](https://github.com/Canybardeloton)) and Joaquim ([@CrystxlSith](https://github.com/CrystxlSith)).
