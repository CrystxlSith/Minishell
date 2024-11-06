#!/bin/bash

dir=$(pwd)

valgrind --show-leak-kinds=all --show-reachable=yes --leak-check=full --track-origins=yes --track-fds=yes --child-silent-after-fork=yes --suppressions=readline.supp ./minishell

#add if needed