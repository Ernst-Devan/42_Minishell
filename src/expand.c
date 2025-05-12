#include <libft.h>
#include <parsing.h>

char *replace_var(char *str, char **env) {
	char *variable;
	char *buffer;

	variable = find_env(str, env);
	if (!variable)
		return ("\0");
	buffer = ft_strdup(variable);
	if (!buffer)
		return ("\0");
	return (buffer);
}

char **insert_list_env(char *input, char **env) {
  char **list_env;
  char temp[ENV_MAX];
  char *variable;
  size_t count_env;
  size_t i;
  size_t increase;

  count_env = count_characters(input, "$");
  list_env = malloc((count_env + 1) * sizeof(char *));
  if (!list_env)
    return (NULL);
  i = 0;

  while (i < count_env) 
	{
    input = ft_strchr(input, '$');
    input++;
    increase = ft_strccpy(temp, input, ' ');
    input += increase;
	ft_strlcat(temp, "=" , ENV_MAX);
    variable = replace_var(temp, env);
	list_env[i] = ft_strdup(variable);
    ft_strlcpy(temp, "\0", 1);
    i++;
  }
  list_env[i] = NULL;
  return (list_env);
}

void	check_var_env(char **list_env,char *buffer, size_t *i, size_t *j, size_t buffer_size)
{
	buffer[*i] = '\0';
	ft_strlcat(buffer, list_env[*j], buffer_size);
	*i += ft_strlen(list_env[*j]);
	*j += 1;
}
