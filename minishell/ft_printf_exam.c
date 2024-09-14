#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int	put_string(char *s)
{
	int	i;

	if (!s)
		return (put_string("(null)"));
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
int put_num(int n)
{
    char res;
    long nb;
    int ret = 0;

    nb = n;
    if (nb < 0)
        nb *= -1;
    else if(nb >= 0  && nb <= 9)
    {
        res = nb + '0';
        write(1,&res,1);
        ret++;
    }
    else if(nb > 9)
    {
        put_num(nb / 10);
        put_num(nb % 10);
    }
    return(ret);
}

int put_hex(unsigned int n)
{
    char *hex = "0123456789abcdef";
    int res = 0;
    if(n < 16)
        return(write(1, &hex[n], 1), 1);
    else if(n > 16)
    {
        res += put_hex(n / 16);
        return(res + put_hex(n % 16));
    }
    return(res);
}
int my_fuckin_printf(char c, va_list args)
{
    if (c == 's')
        return(put_string(va_arg (args, char *)));
    else if (c == 'd')
        return(put_num(va_arg (args, int)));
    else if (c == 'x')
        return(put_hex(va_arg (args, unsigned int)));
    return(0);
}
int ft_printf(const char *c, ...)
{
    va_list args;

    va_start(args, c);
    int i = 0;
    int return_value = 0;
    while(c[i])
    {
        if (c[i] =='%' && c[i + 1] == 's' || c[i + 1] == 'd' || c[i + 1] == 'x')
        {
            return_value += my_fuckin_printf(c[i + 1], args);
            i += 2;
        }
        else
        {
            write(1, &c[i], 1);
            return_value ++;
            i++;
        }
    }
    return(return_value);
}
int main()
{
    int i = ft_printf("hello %d %x %s\n",2147483647, 15, "ilyass");
    printf("1>%d\n",i);
    int b = printf("hello %d %x %s\n",2147483647, 15, "ilyass");
    printf("2>%d\n",i);
}