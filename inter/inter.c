#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *s)
{
	int i = 0;

	while (s[i])
		ft_putchar(s[i++]);
}

int ft_isin(char c, char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return 1;
		i++;
	}
	return 0;
}


int main(int ac, char **av)
{
	char buf[256];
	char *s1 = av[1];
	char *s2 = av[2];
	int i = 0;
	int j = 0;

	if (ac != 3)
	{
		ft_putchar('\n');
		return 0;
	}
	while (s1[i])
	{
		if (ft_isin(s1[i], s2) && !ft_isin(s1[i], buf))
		{
			buf[j] = s1[i];
			j++;
		}
		i++;
	}
	ft_putstr(buf);
	return 0;
}
