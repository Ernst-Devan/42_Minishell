
#include "minishell.h"
#include "env_manage.h"
#include "libft.h"
#include "exec.h"
#include "parsing.h"

int minishell(char **env) {
  t_table table;
  char **ms_env;

  ms_env = new_env(env);
  if (!ms_env)
    return (1);
  while (1) {
    table = parsing(ms_env);
    display_table(table);
	//if (exec(table, &ms_env))
    //{
    // Free all the malloc
	//	return (1);
    //}
  }
  // Free all the malloc
  return (0);
}

int main(int ac, char **argv, char **env) {
  (void)ac;
  (void)argv;
  if (minishell(env))
    return (1);
  return (0);
}
