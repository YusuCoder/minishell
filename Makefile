
NAME	:= minishell
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -g
RM		:= rm -rf

LIBFT_PATH  := ./libft
OBJ_PATH	:= ./obj
P_SRC_PATH	:= ./p_srcs
E_SRC_PATH	:= ./e_srcs
MAIN		:= main.c
SRC_FILES	:= ./p_srcs/i_init_cmd.c \
				./p_srcs/i_handle_signals.c \
				./p_srcs/errors.c \
				./p_srcs/t_tokenize.c \
				./p_srcs/t_add_tokens.c \
				./p_srcs/t_utils.c \
				./p_srcs/parse.c \
				./p_srcs/set_envp.c \
				./p_srcs/count_commands.c \
				./p_srcs/sub_cmd_arrays.c \
				./p_srcs/expanding.c \
				./p_srcs/expanding_1.c \
				./p_srcs/expanding_2.c \
				./p_srcs/quote_handling.c \
				./e_srcs/list/command_list.c \
				./e_srcs/list/list_handler.c \
				./e_srcs/environment/env_set.c \
				./e_srcs/environment/env_sort.c \
				./e_srcs/environment/env_value.c \
				./e_srcs/custom_functions/custom_functions.c \
				./e_srcs/environment/env_var.c \
				./e_srcs/builtins/builtin_checker.c \
				./e_srcs/builtins/cd.c \
				./e_srcs/builtins/echo.c \
				./e_srcs/builtins/env.c \
				./e_srcs/builtins/exit.c \
				./e_srcs/builtins/export.c \
				./e_srcs/builtins/export_utils.c \
				./e_srcs/builtins/pwd.c \
				./e_srcs/builtins/unset.c \
				./e_srcs/execute.c \
				./e_srcs/execute_utils.c \
				./e_srcs/cleanup.c \
				./e_srcs/error.c \
				./e_srcs/free.c

OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES:.c=.o))
MAIN_OBJ	:= $(OBJ_PATH)/main.o

LIBFT		:= $(LIBFT_PATH)/libft.a

all: update $(NAME)

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE COMMAND IN MAC
rl:
	@brew install readline

#IF SUBMODULE IS NOT EXISTS IN THE REPO, FETCH AND UPDATE
update:
	@git submodule update --init --recursive

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE LINUX (LINUX ONLY)
linux: update readline_linux_install $(NAME)

#COMMAND TO INSTALL READLINE ON LINUX
readline_linux_install:
	@sudo apt install libreadline-dev

$(NAME): $(MAIN_OBJ) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(P_SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re git_sub_update
