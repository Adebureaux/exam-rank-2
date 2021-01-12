#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int ret;
int width;
int prec;
int i;

int ft_strlen(char *str)
{
	int j = 0;

	while (str[j])
		j++;
	return (j);
}

char *ft_strncpy(char *src, char *dst, int n)
{
	int j = 0;

	while (src[j] && j < n)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int ft_putstr(char *str)
{
	int j = 0;

	while (str[j])
		ft_putchar(str[j++]);
	return (j);
}

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_atoi(char *str)
{
	int n = 0;

	while (ft_isdigit(str[i]))
	{
		n += str[i] - '0';
		i++;
		if (ft_isdigit(str[i]))
			n *= 10;
	}
	return (n);
}

int display_s(char *str)
{
	int len;
	char *dst;

	len = str ? ft_strlen(str) : 6;
	if (prec != -1)
		len = prec > len ? len : prec;
	width -= len;
	dst = malloc(sizeof(char) * (len + 1));
	while (width-- > 0)
		ret += ft_putchar(' ');
	if (!str)
		dst = ft_strncpy("(null)", dst, len);
	else
		ft_strncpy(str, dst, len);
	ret += ft_putstr(dst);
	free(dst);
	return (1);
}

int nbrlen(int n, int base)
{
	int j = 0;

	if (n <= 0)
	{
		n *= -1;
		j++;
	}
	while (n > 0)
	{
		n /= base;
		j++;
	}
	return (j);
}

void ft_putnbr_base(int n, char *base)
{
	int size;

	size = ft_strlen(base);
	if (n < 0)
	{
		n *= -1;
		ret += ft_putchar('-');
	}
	if (n >= size)
		ft_putnbr_base((int)(n / size), base);
	ret += ft_putchar(base[n % size]);
}

int display_d(int n)
{
	char base[] = "0123456789";
	int len;

	len = nbrlen(n, 10);
	width -= prec > 0 ? prec : len;
	prec -= len;
	if (n < 0 && prec >= 0)
	{
		prec++;
		width--;
	}
	while (width-- > 0)
		ret += ft_putchar(' ');
	if (n < 0)
	{
		ret += ft_putchar('-');
		n *= -1;
	}
	while (prec-- > 0)
		ret += ft_putchar('0');
	ft_putnbr_base(n, base);
	return (1);
}

int display_x(unsigned long u)
{
	char base[] = "0123456789abcdef";
	int len;

	len = nbrlen(u, 16);
	width -= prec > 0 ? prec : len;
	prec -= len;
	if (u < 0 && prec >= 0)
	{
		prec++;
		width--;
	}
	while (width-- > 0)
		ret += ft_putchar(' ');
	if (u < 0)
	{
		ret += ft_putchar('-');
		u *= -1;
	}
	while (prec-- > 0)
		ret += ft_putchar('0');
	ft_putnbr_base(u, base);
	return (1);
}

void parse(va_list vl, char *str)
{
	i++;
	width = 0;
	prec = -1;
	if (ft_isdigit(str[i]))
		width = ft_atoi(str);
	if (str[i] == '.')
	{
		i++;
		if (ft_isdigit(str[i]))
			prec = ft_atoi(str);
		else
			prec = 0;
	}
	if (str[i] == 's')
		i += display_s(va_arg(vl, char*));
	else if (str[i] == 'd')
		i += display_d(va_arg(vl, int));
	else if (str[i] == 'x')
		i += display_x(va_arg(vl, unsigned long));
}

int ft_printf(const char *str, ...)
{
	va_list vl;

	ret = 0;
	i = 0;
	va_start(vl, str);
	while (str[i])
	{
		if (str[i] == '%')
			parse(vl, (char*)str);
		if (str[i])
			ret += ft_putchar(str[i]);
		else
			break ;
		i++;
	}
	va_end(vl);
	return (ret);
}

int main()
{
	printf(" | ret = %d\n", printf("|%s", "1string"));
	printf(" | ret = %d\n", ft_printf("|%s", "1string"));

	printf(" | ret = %d\n", printf("|%s|", "AYAYA"));
	printf(" | ret = %d\n", ft_printf("|%s|", "AYAYA"));

	printf(" | ret = %d\n", printf("this string = |%s|", "Sample str"));
	printf(" | ret = %d\n", ft_printf("this string = |%s|", "Sample str"));

	printf(" | ret = %d\n", printf("string = |%20.8s|", "Sample str"));
	printf(" | ret = %d\n", ft_printf("string = |%20.8s|", "Sample str"));

	printf(" | ret = %d\n", printf("string = |%20.2s|", NULL));
	printf(" | ret = %d\n", ft_printf("string = |%20.2s|", NULL));

	printf(" | ret = %d\n", printf("string = |%.s|", NULL));
	printf(" | ret = %d\n", ft_printf("string = |%.s|", NULL));

	printf(" | ret = %d\n", printf("aaaa%30.20dabcdef", -100));
	printf(" | ret = %d\n", ft_printf("aaaa%30.20dabcdef", -100));

	printf(" | ret = %d\n", printf("aaaa%.5dabcdef", -100));
	printf(" | ret = %d\n", ft_printf("aaaa%.5dabcdef", -100));

	printf(" | ret = %d\n", printf("%5d", -123));
	printf(" | ret = %d\n", ft_printf("%5d", -123));

	printf(" | ret = %d\n", printf("%5d", 0));
	printf(" | ret = %d\n", ft_printf("%5d", 0));

	printf(" | ret = %d\n", printf("%5d", 1));
	printf(" | ret = %d\n", ft_printf("%5d", 1));

	printf(" | ret = %d\n", printf("%d", 0));
	printf(" | ret = %d\n", ft_printf("%d", 0));

	printf(" | ret = %d\n", printf("%x", 42));
	printf(" | ret = %d\n", ft_printf("%x", 42));

	printf(" | ret = %d\n", printf("%20.10x", 42));
	printf(" | ret = %d\n", ft_printf("%20.10x", 42));

	printf(" | ret = %d\n", printf("%20.10x", 42981234));
	printf(" | ret = %d\n", ft_printf("%20.10x", 42981234));
	return (1);
}
