#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


static int	get_value(char c)
{
	if (isdigit(c))
		return (c - '0');
	if (islower(c))
		return (c - 'a' + 10);
	return (c - 'A' + 10);
}

int			ft_atoi_base(const char *str, char *base)
{
	int sum;
	int i;
	int sign;
	int baselen;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	sum = 0;
	baselen = strlen(base);
	while (str[i])
	{
		sum *= baselen;
		sum += get_value(str[i]);
		i++;
	}
	return (sign * sum);
}
