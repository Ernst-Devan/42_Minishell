// DONT FORGET THE HEADER


//! Secure if the env is empty

#include "libft.h"

char *find_env(char *str, char **env)
{
	int	count;
	int	i;

	i = 0;
	count = ft_strlen(str);
	while (env[i])
    {
		if (ft_strncmp(str, env[i], count) == 0)
			return (env[i] + count + 1);
		i++;
    }
	return (NULL);
}
