
#ifndef MINISHELL_H
# define MINISHELL_H

// # define RED "\x1b[31m"
// # define GREEN "\x1b[32m"
// # define YELLOW "\x1b[33m"
// # define BLUE "\x1b[24m"
// # define MAGENTA "\x1b[35m"
// # define CYAN "\x1b[36m"
// # define WHITE "\x1b[97m"
// # define RESET "\x1b[0m"

# define RED ""
# define GREEN ""
# define YELLOW ""
# define BLUE ""
# define MAGENTA ""
# define CYAN ""
# define WHITE ""
# define RESET ""

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <termios.h>

#define PIPE 124
#define LESS 60
#define GREATER 62
#define AMP 38
#define SQUOTE 39
#define DQUOTE 34
#define DEFAULT 0
#define DOLLAR '$'

#ifndef TAB
#define TAB 9
#endif

#ifndef SPACE
#define SPACE 32
#endif

#include "../libft/libft.h"

typedef struct s_data t_data;

/*---Struct for files and fd---*/
typedef struct s_fd
{
	char	*file;
	int		fd;
}			t_fd;

typedef struct s_sub_commands
{
	char	**sub_cmd_array; //avlue of arguments (commands) each sub-command has
	int		sub_argc_count; //number of arguments (commands) each sub-command has
	char	**arguments;
	int		argc;
	char	**argv;
	t_fd	input_fd;
	t_fd	output_fd;
	t_fd	error_fd;
	int		is_heredoc;
	char	*is_delimeter;
	int		append;
	int		pid;
}			t_sub_commands;

/*---General command struct---*/
typedef struct s_commands
{
	char			**tokens;
	t_ryusupov		**env;
	int			exit_code;
	int				*pipe;
	int				cmd_num; //number of commands separated with pipe
	char			**envp;
	char			**path;
	t_sub_commands	*sub_command; //array of sub-commands seperated with pipes
}					t_command;

typedef enum s_status
{
	COUNT,
	SET,
	SKIP,
	SAVE,
	ONE,
	MULTIPLE,
}			t_status;

typedef enum s_type
{
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
}			t_type;

typedef struct s_redir
{
	t_type			type;
	char			*name;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	int				index;
	char			**cmd_array;
	char			**args;		//array of arguments of each command
	int				args_num;	//number of arguments of each command
	int				pipe_fd[2];
	int				is_heredoc;	// Flag indicating if heredoc is used
	int				is_redir_input;	// Flag indicating if input redirection
	int				is_redir_output;	// Flag indicating if output redirection
	char			*heredoc_input;
	t_redir			*input_list;
	t_redir			*output_list;
	struct s_cmd	*next;
}				t_cmd;

/*---General program struct---*/
typedef struct s_data
{
	char		**tokens;
	char		**env;
	int			cmd_num;	//number of commands separated with pipe
	t_cmd		*cmd_list;	//list of commands seperated with pipes
	int			*exit_code;
	int			heredoc_fd[2];
	char		*last_arg;
}				t_data;

typedef struct s_quote_state
{
	int		in_single_quote;
	int		in_double_quote;
	int		squote;
	int		dquote;
	int		i;
	int		j;
	int		found_quote;
	char	quote_char;
	char	*result;

}   t_quote_state;

typedef enum s_process
{
	INIT,
	RES,
	CHILD_PROCESS,
}			t_process;

/*-----------SIGNALS----------*/
void	_init_terminal(void);
void	_handle_signals(t_process stats, t_data *data);
void	determine_exit_code(int *exit_code);
/*--------Error messages---------*/
void	_err_msg(char *msg, char err_code);
void	_free_it(char **p);
void	free_ptr(void *ptr);
void	ft_perror_parsing(char *msg1, char *msg2, char *arg, int *exit_code);
/*----------TOKENIZING-----------*/
char	**tokenizing(const char *str);
int 	take_tokens(char **token, const char *str, int i);
int		matching_quotes(const char *str);
int		count_words(const char *str, int i);
int		count_tokens(char token);
int		get_word_len(const char *str, int i);
int		count_str(char c);
/*-----------PARSING-------------*/
int		parse(char	**t, t_data *exit_code);
int		check_beginning_and_end(char **t, int i);
int		parse_redirs(char *current, char *next);
int		count_str(char c);
int		quotes_check(char *t);
int		is_empty(const char *str);
/*--------QUOTE HANDLING----------*/
void	quote_handing(t_cmd *cmd_list);
char 	*remove_last_quote(const char *token);
void 	quote_handling_r(char **tokens);
/*------------EXPANDING------------*/
void 	expand(char **tokens, char **env, t_data *exit_code);
int		not_in_squote(char *token, int i);
int		is_exeption(char c);
int		still_dollar_sign_there(char *token);
char	*dollar_sign(char *sign, char *token,  char **env, t_data *data);
char	*replace_question(const char *var, int *exit_code);
char 	*replace_var(char *str, char *var, int i);
char 	*remove_replace(char *str, char *var, int i);
char	*get_v_name(char *token);
char	*get_e_name(char *v_name, char **env);
char	*remove_var(char *token, char *v_name);
char	*replace_token(char *token, char *e_name);
/*------------EXPANDING HEREDOC-----------*/
void	expand_heredoc(char **tokens, char **env, t_data *data);
char	*get_v_name_heredoc(char *token);
char	*get_e_name_heredoc(char *v_name, char **env, char *original_v_name);
char	*dollar_sign_heredoc(char *sign, char *token, char **env, t_data *data);
int		still_dollar_heredoc(char *token);
int		count_string_heredoc(char *token);
char	*fill_e_name(char *line, int i);
char	*get_c_string(char *token);
char	*get_x_string(char	*token);
int		count_string(char	*token);
/*------------Sub command bouilding-------------*/
// void	sub_cmds_array(t_command *cmd, char **tokens);
// int		count_commands(char **tokens, t_command *cmd);
// int		count_cmds(char	**token);
// int		token_count(t_command *cmd, char **tokens, int i, int j);
// int		build_cmds(char	**tokens, t_command *cmd);

/*--------------------*/
/*  Custom finctions  */
/*--------------------*/
char	**split_str(char const *s, char c);
char	*my_strjoin(const char *str1, const char *str2, const char *str3);
char	*my_strndup(const char *str, int len);
void	*my_realloc(void *ptr, int old_size, int new_size);
int		is_number(char *arg);

/*------------------------*/
/*  Environment handling  */
/*------------------------*/
char	**env_create_new(void);
char	**env_set(char **env);
int		env_len(char **env);
void	env_increase_shlvl(char ***env);
void	env_reset_oldpwd(char ***env);
char	*env_var_create(const char *name, const char *value);
int		env_var_find(char **env, const char *name);
int		env_var_find_no_value(char **env, const char *name);
int		env_var_add(char ***env, char *new_env_var);
int		env_var_remove(char ***env, int index);
char	*env_value_get(char **env, const char *name);
void	env_value_delete(char **env, char *name);
void	env_value_change(char **env, const char *name, const char *value);
int		env_value_change_pwd_oldpwd(char *prev_dir, char **env, int *exit_code);
char	**env_sort(char **env);
void	quicksort(char **arr, int low, int high);
int		partition(char **arr, int low, int high);
void	swap(char **a, char **b);

/*------------------*/
/*  Array handling  */
/*------------------*/
char	**array_copy(char **array);
int		array_len(char **array);

/*-------------------------*/
/*  Command list handling  */
/*-------------------------*/
void	cmd_list_handler(t_data *data);
int		cmd_list_add_new(t_cmd **head, char **tokens, int len, int index);
char	**cmd_list_set_args(char **tokens, int len, int index);
int		count_commands(char **tokens);
int		count_arguments(char **tokens, int index);
void	cmd_list_add(t_cmd *head, t_cmd *new);
t_cmd	*cmd_list_last(t_cmd *head);
t_cmd	*cmd_list_find(t_cmd *head, int index);

/*-----------------------------*/
/*  Redirection list handling  */
/*-----------------------------*/
int		is_redirection(char *arg);
int		is_heredoc(char *arg);
int		is_redir_input(char *arg);
int		is_redir_otput(char *arg);
int		is_redir_append(char *arg);
void	redir_list_handler(t_data *data);
int		redir_check(t_cmd *cmd);
int		redir_count(char **args);
int		redir_create(t_cmd *cmd, int index, t_type type);
int		new_redir_handler(t_cmd *cmd, char *name, t_type type);
int		new_redir_create(t_redir **redir_list, char *name, t_type type);
void	redir_list_add(t_redir *head, t_redir *new);
t_redir	*redir_list_last(t_redir *head);
int		set_cmd_array(t_cmd *cmd);
void	cmd_array_handler(char **args, int *counter, char **cmd_array, \
							t_status status);

/*------------------------*/
/*  Redirection handling  */
/*------------------------*/
int		redirection_handler(t_cmd *cmd, int *exit_code);
int		redir_output_handler(t_redir *output_list);
int		redir_input_handler(t_redir *input_list, char *heredoc_input, \
							int *exit_code);
int		redir_input_file(t_redir *redir, int *exit_code);
int		redir_input_heredoc(char *heredoc_input);

/*--------------------*/
/*  Heredoc handling  */
/*--------------------*/
void	heredoc_handler(t_data *data);
void	heredoc_input_handler(t_data *data, t_cmd *cmd);
int heredoc_readline(t_cmd *cmd, char *delimiter, t_status status, char **env, t_data *data);
int		heredoc_save_input(t_cmd *cmd, char *line);

/*-------------*/
/*  Executing  */
/*-------------*/
void	execute(t_data *data);
void	execute_single_command(t_data *data, t_cmd *cmd, t_status status);
void	execute_builtin(t_data *data, t_cmd *cmd);
void	execute_external(t_data *data, t_cmd *cmd);
void	fork_external(t_data *data, t_cmd *cmd);
void	execute_multiple_commands(t_data *data);
int		pipe_set_all(t_cmd *cmd_list);
void	pipe_close_all(t_cmd *cmd_list);
void	pipe_redirection_handler(t_data *data, t_cmd *curr_cmd);
void	wait_processes(pid_t last_pid, int *last_exit_code);
int		is_accessable(char *cmd_name, char **cmd_path, char **env);
int		is_executable(char *cmd_path);
char	*set_cmd_path(char *str);
void	print_wrong_command(char *arg, int *exit_code);
void	print_wrong_path(char *arg, int *exit_code);

/*--------------------*/
/*  Builtin commands  */
/*--------------------*/
int		is_builtin(char *arg);
int		is_cd(char *arg);
int		is_pwd(char *arg);
int		is_env(char *arg);
int		is_echo(char *arg);

/*---- cd command ----*/
int		execute_cd(char **args, char **env, int *exit_code);
int		cd_home_dir(char **env, int *exit_code);
int		cd_dash_arg(char **env, int *exit_code);
int		change_directory(char *path, int *exit_code);

/*---- echo command ----*/
int		execute_echo(char **args, int *exit_code);
int		echo_skip_all_n(char **args, int *i);
int		echo_is_all_n(char *arg);
void	echo_print_arg(char *arg, int exit_code);

/*---- env command ----*/
int		execute_env(char **env, int *exit_code);

/*---- exit command ----*/
void	execute_exit(t_data *data, char **args, int *exit_code);

/*---- export command ----*/
int		execute_export(char **args, char ***env, int *exit_code);
int		export_no_args(char **env, int *exit_code);
int		export_with_args(char *arg, char ***env, int *exit_code);
int		export_arg_with_value(char *arg, char *equal_sign,
			char ***env, int *exit_code);
int		export_arg_no_value(char *arg, char ***env, int *exit_code);
int		export_update_env(char ***env, const char *name, const char *value, int overwrite);

/*---- pwd command ----*/
int		execute_pwd(int *exit_code);

/*---- unset command ----*/
int		execute_unset(char **args, char ***env, int *exit_code);

/*---------------------*/
/*  Cleanup functions  */
/*---------------------*/
void	free_array(char **array);
void	free_redir_list(t_redir **head);
void	free_cmd_list(t_cmd **head);
void	free_exit(t_data *data, int exit_code);
void	free_error_exit(t_data *data, int exit_code, char *error_msg);
void	cleanup(t_data *data);

/*-----------------*/
/*  Error handler  */
/*-----------------*/
void	ft_perror(char *msg1, char *arg, char *msg2);

#endif
