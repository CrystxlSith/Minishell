# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 10:25:55 by agiliber          #+#    #+#              #
#    Updated: 2024/10/02 16:49:33 by agiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------------------------------
# 								HEADER
# ------------------------------------------------------------------------------

NAME_LIB = libft.a
NAME = minishell
NAME_A = minishell.a

# ------------------------------------------------------------------------------
# 								COMPILATION
# ------------------------------------------------------------------------------

CC = cc
CFLAGS = -g3 -Wall -Wextra -I./includes/
RM = rm -rf
LIBFT_FLAGS = -L./$(LIB_DIR) -l:libft.a
CLEAN = $(MAKE) clean
F_CLEAN = $(MAKE) fclean

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
RESET  = \033[0m

# ------------------------------------------------------------------------------
# 									DIR
# ------------------------------------------------------------------------------

LIB_DIR = libft/
BUILTINS_DIR = src/builtins/
LEXER_DIR = src/lexer/
PARSER_DIR = src/parser/
REDIREC_DIR = src/redirections/
SIGNAL_DIR = src/signals/

SRC_DIR = $(BUILTINS_DIR) $(LEXER_DIR) $(PARSER_DIR) $(REDIREC_DIR) $(SIGNAL_DIR)

BUILTINS_OBJ_DIR = obj/builtins/
LEXER_OBJ_DIR = obj/lexer/
PARSER_OBJ_DIR = obj/parser/
REDIREC_OBJ_DIR = obj/redirections/
SIGNAL_OBJ_DIR = obj/signal/

OBJ_DIR = $(BUILTINS_OBJ_DIR) $(LEXER_OBJ_DIR) $(PARSER_OBJ_DIR) $(REDIREC_OBJ_DIR) $(SIGNAL_OBJ_DIR)

BUILTINS_OBJ_DEP = dep/builtins/
LEXER_OBJ_DEP = dep/lexer/
PARSER_OBJ_DEP = dep/parser/
REDIREC_OBJ_DEP = dep/redirections/
SIGNAL_OBJ_DEP = dep/signals/

DEP_DIR = $(BUILTINS_OBJ_DEP) $(LEXER_OBJ_DEP) $(PARSER_OBJ_DEP) $(REDIREC_OBJ_DEP) $(SIGNAL_OBJ_DEP)

# ------------------------------------------------------------------------------
# 									FILES
# ------------------------------------------------------------------------------

BUILTINS = builtins.c echo.c cd.c env.c export.c ft_export_utiles.c \
	ft_utiles_cd_prev.c ft_utiles_cd.c ft_utiles_echo.c ft_utiles_echo2.c \
	pwd.c unset.c

LEXER = handler.c init_lexer.c lexer_utils.c lexer.c lex_error_handler.c

PARSER = parser_utils.c parser.c parser_utils2.c parser_utils_3.c print_error.c signals.c

REDIREC = exec_cmd_minishell.c get_path_cmd.c ft_piping_utils.c ft_redir_utils.c \
	exec_pipe_cmd.c ft_multi_piping_utils.c

SIGNALS =

MAIN = main.c

BUILTINSF = $(addprefix $(BUILTINS_DIR), $(BUILTINS))
LEXERF = $(addprefix $(LEXER_DIR), $(LEXER))
PARSERF = $(addprefix $(PARSER_DIR), $(PARSER))
REDIRECF = $(addprefix $(REDIREC_DIR), $(REDIREC))
SIGNALSF = $(addprefix $(SIGNAL_DIR), $(SIGNALS))

BUILTINS_OBJ = $(addprefix $(BUILTINS_OBJ_DIR), $(BUILTINS:%.c=%.o))
LEXER_OBJ = $(addprefix $(LEXER_OBJ_DIR), $(LEXER:%.c=%.o))
PARSER_OBJ = $(addprefix $(PARSER_OBJ_DIR), $(PARSER:%.c=%.o))
REDIREC_OBJ = $(addprefix $(REDIREC_OBJ_DIR), $(REDIREC:%.c=%.o))
SIGNAL_OBJ = $(addprefix $(SIGNAL_OBJ_DIR), $(SIGNALS:%.c=%.o))
MAIN_OBJ = main.o

BUILTINS_DEP = $(addprefix $(BUILTINS_OBJ_DEP), $(BUILTINS_OBJ:%.o=%.d))
LEXER_DEP = $(addprefix $(LEXER_OBJ_DEP), $(LEXER_OBJ:%.o=%.d))
PARSER_DEP = $(addprefix $(PARSER_OBJ_DEP), $(PARSER_OBJ:%.o=%.d))
REDIREC_DEP = $(addprefix $(REDIREC_OBJ_DEP), $(REDIREC_OBJ:%.o=%.d))
SIGNAL_DEP = $(addprefix $(SIGNAL_OBJ_DEP), $(SIGNAL_OBJ:%.o=%.d))

SRC = $(BUILTINSF) $(LEXERF) $(PARSERF) $(REDIRECF) $(MAIN) $(SIGNALSF)
OBJ = $(BUILTINS_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(REDIREC_OBJ) $(MAIN_OBJ)
DEP = $(BUILTINS_DEP) $(LEXER_DEP) $(PARSER_DEP) $(REDIREC_DEP)

LIBFT_OBJ = $(addprefix $(LIB_DIR), $(NAME_LIB))

# ------------------------------------------------------------------------------
# 									COMMANDS
# ------------------------------------------------------------------------------

all : $(NAME)

.SILENT : $(NAME) $(NAME_A) $(BUILTINS_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) \
	$(REDIREC_OBJ) $(MAIN_OBJ) $(BUILTINS_OBJ_DIR) $(LEXER_OBJ_DIR) \
	$(PARSER_OBJ_DIR) $(REDIREC_OBJ_DIR) $(BUILTINS_OBJ_DEP) $(LEXER_OBJ_DEP) \
	$(PARSER_OBJ_DEP) $(REDIREC_OBJ_DEP) $(SIG) $(SIGNAL_OBJ_DIR) $(SIGNAL_OBJ_DEP) \
	$(OBJ_DIR) $(DEP_DIR) $(DEP_DIR) $(CLEAN) $(F_CLEAN)

$(NAME) : $(NAME_A) $(OBJ)
	echo "${CYAN}Compiling Minishell...${RESET}"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -lreadline $(NAME_A) -o $@
	echo "${GREEN}Succes!!!${RESET}"

$(NAME_A) : $(OBJ)
	echo "${CYAN}Compiling libft...${RESET}"
	$(MAKE) --no-print-directory -C $(LIB_DIR)
	cp libft/libft.a $(NAME_A)
	ar rc $(NAME_A) $(OBJ)

$(BUILTINS_OBJ_DIR)%.o : $(BUILTINS_DIR)%.c | $(BUILTINS_OBJ_DIR) $(BUILTINS_OBJ_DEP)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(BUILTINS_OBJ_DEP)$*.d

$(LEXER_OBJ_DIR)%.o : $(LEXER_DIR)%.c | $(LEXER_OBJ_DIR) $(LEXER_OBJ_DEP)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(LEXER_OBJ_DEP)$*.d

$(PARSER_OBJ_DIR)%.o : $(PARSER_DIR)%.c | $(PARSER_OBJ_DIR) $(PARSER_OBJ_DEP)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(PARSER_OBJ_DEP)$*.d

$(REDIREC_OBJ_DIR)%.o : $(REDIREC_DIR)%.c | $(REDIREC_OBJ_DIR) $(REDIREC_OBJ_DEP)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(REDIREC_OBJ_DEP)$*.d

$(SIGNAL_OBJ_DIR)%.o : $(SIGNAL_DIR)%.c | $(SIGNAL_OBJ_DIR) $(SIGNAL_OBJ_DEP)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(SIGNAL_OBJ_DEP)$*.d

$(MAIN_OBJ) : $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILTINS_OBJ_DIR) :
	mkdir -p $(BUILTINS_OBJ_DIR)

$(LEXER_OBJ_DIR) :
	mkdir -p $(LEXER_OBJ_DIR)

$(PARSER_OBJ_DIR) :
	mkdir -p $(PARSER_OBJ_DIR)

$(REDIREC_OBJ_DIR) :
	mkdir -p $(REDIREC_OBJ_DIR)

$(BUILTINS_OBJ_DEP) :
	mkdir -p $(BUILTINS_OBJ_DEP)

$(LEXER_OBJ_DEP) :
	mkdir -p $(LEXER_OBJ_DEP)

$(PARSER_OBJ_DEP) :
	mkdir -p $(PARSER_OBJ_DEP)

$(REDIREC_OBJ_DEP) :
	mkdir -p $(REDIREC_OBJ_DEP)

$(SIGNAL_OBJ_DIR) :
	mkdir -p $(SIGNAL_OBJ_DIR)


clean:
	@echo "${RED}Cleaning libft && Minishell...${RESET}"
	$(CLEAN) --no-print-directory -C $(LIB_DIR)
	$(RM) $(OBJ_DIR)
	$(RM) $(DEP_DIR)
	$(RM) $(MAIN_OBJ)
	@echo "${GREEN}Succes!!!${RESET}"

fclean: clean
	echo "${RED}Cleaning exucutable files...${RESET}"
	$(F_CLEAN) --no-print-directory -C $(LIB_DIR)
	rm -f $(NAME_A)
	echo "${GREEN}Succes!!!${RESET}"

re : fclean all

.PHONY : all clean fclean re

-include $(DEP)
