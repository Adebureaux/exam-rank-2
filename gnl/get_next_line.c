#include "get_next_line.h"
#include <stdio.h>

void ft_bzero(char *str, int size)
{
	int i = 0;

	while (i++ < size)
		str[i++] = '\0';
}

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char *ft_strcpy(char *src, char *dst)
{
	int i = 0;

	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int get_next_line(char **line)
{
	int rd = 1;
	int i = 0;
	int ret = 1;
	char str[10000];

	ft_bzero(str, 10000);
	if (!line)
		return (-1);
	while (i < 10000)
	{
		rd = read(0, &str[i], 1);
		if (rd == 0)
		{
			ret = 0;
			break ;
		}
		else if (str[i] == '\n')
			break ;
		else if (rd < 0)
			return (-1);
		i++;
	}
	str[i] = '\0';
	if (!(*line = malloc(sizeof(char) * ft_strlen(str))))
		return (-1);
	*line = ft_strcpy(str, *line);
	return (ret);
}
