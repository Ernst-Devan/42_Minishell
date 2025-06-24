/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:14:26 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 10:43:55 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H 
# define EXEC_H

# include "parsing.h"

int		exec_bin(t_table table, char **env);
int		exec_bin(t_table table, char **env);
t_shell	exec(t_table table, t_shell shell);

int		export(t_cmd cmd, char ***env);
int		find_env_variable(char **env, char *str);
int		edit_variable_env(char ***env, char *data);
int		add_variable_env(char ***env, char *data);

int		cd(t_cmd cmd, char ***env);
int		echo(t_cmd command);
int		pwd(t_cmd cmd);
int		unset(t_cmd cmd, char ***env);
void	ms_exit(t_cmd cmd, char **env, t_shell *shell, t_table table);
int		check_name(char	*str);
void	export_without_param(char **env);
void	print_export_one_val(char *str);
int		edit_variable_env(char ***env, char *data);
int		add_variable_env(char ***env, char *data);

int		env_builtin(char **env, t_cmd cmd);

int		exec_builtins(t_cmd cmd, t_shell *shl, t_table tbl, int sv_std[2]);

char	*remove_consecutiv_slash(char *path);
char	*remove_dot_slash(char *path);
char	*remove_if_dotdot(char *path);

char	*update_pwd(char *pwd);
char	*get_pwd(char **env);
char	*build_pwd(char *pwd, char *path);
int		set_pwd(char *pwd, char ***env);

int		manage_ctrl_c_var(int val);
void	sig_hand(int sig);
int		useless_function(void);

int		open_heredoc(char *str, char **eof, char **name);
int		open_in_file(char *str);
void	heredoc(int fd, char *eof);
int		open_in_heredoc_cmd(t_cmd *cmd, int *nb_files);
int		open_in_cmd(t_cmd *cmd);
int		manage_in(t_cmd *cmds, t_table table, int *nb_files);

int		manage_out(t_cmd *cmds, t_table table);
int		open_out_cmd(t_cmd *cmd);
int		open_out_file(char *str);
int		open_append(char *str);
void	close_fd(t_table table);

int		lexical_analyser(char *input);
void	close_fd(t_table table);

int		find_env_variable(char **env, char *str);
int		var_env_len(char *str);
char	*find_n(char **env, int nb);
char	*find_first(char **env);
int		count_bigger_than(char *str, char **env);

int		make_file_heredoc(char **eof, char **name, char *str, int n);
void	heredoc(int fd, char *eof);
int		manage_heredoc(int fd, char *str_in);
int		open_heredoc(char *str, char **eof, char **name);
int		open_in_heredoc_cmd(t_cmd *cmd, int *nb_files);
char	**try_access(char **name, int i);

int		len_without_slashslash(char *path);
char	*remove_consecutiv_slash(char *path);
int		len_without_dotslash(char *path);
void	make_newpath_without_dotslash(int len, char *path, char *new_path);

#endif
