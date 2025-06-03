#include "libft.h"
#include "parsing.h"
#include <stddef.h>

size_t	alloc_error_code(t_shell shell, size_t *i)
{
	char	*error;
	size_t	count;

	error = ft_itoa(shell.error_code);
	count = ft_strlen(error);
	free(error);
	*i += 1;
	return (count);
}

size_t	size_allocation_expand(char *input, t_shell shell)
{
	char	*full;
	char	*variable;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] == '$')
		{
			full = detect_full_variable(&input[i]);
			if (!full)
				break;
			variable = find_env(full, shell.env);
			if (full[0] == '?')
				count += alloc_error_code(shell, &i);
			i += ft_strlen(full) - 1;
			free(full);
			count += ft_strlen(variable);
		}
		i++;
		count++;
	}
	return (count * 2);
}

