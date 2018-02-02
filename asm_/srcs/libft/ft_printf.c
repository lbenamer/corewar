/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <aboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:57:42 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/30 02:20:29 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	len_return(t_conv *t)
{
	t->len_return = 0;
	if (t->conv == 's')
		conv_s(t);
	else if (t->conv == 'd' || t->conv == 'i')
		conv_d(t);
	else if (t->conv == 'c')
		conv_c(t);
	else if (t->conv == 'u')
		conv_u(t);
}

void	get_conv(const char *s, t_conv *t)
{
	if ((int)ft_strlen(s) > 1 && (ft_isalpha(t->conv) == 1 || t->conv == '%'))
	{
		if (t->conv == 's')
			t->s = (char *)va_arg(t->arguments, char *);
		else if (t->conv == 'd' || t->conv == 'i')
			t->d = (int)va_arg(t->arguments, long long int);
		else if (t->conv == 'u')
			t->u = (unsigned int)va_arg(t->arguments, unsigned long long int);
		else if (t->conv == 'c')
			t->c = (unsigned int)va_arg(t->arguments, unsigned long int);
		len_return(t);
	}
}

void	printstr(const char *s, t_conv *t)
{
	int len;

	len = 0;
	while ((s[t->i] != '%' && s[t->i] != '\0') && s[t->i] + 1)
	{
		t->i++;
		t->j++;
		len++;
	}
	t->print = ft_strsub(s, (unsigned)(t->i - len), (size_t)len);
	ft_putstr_fd(t->print, t->fd);
	free(t->print);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_conv	t;

	t.fd = fd;
	init_start(&t);
	va_start(t.arguments, format);
	while (format[t.i] != '\0' && t.i <= (int)ft_strlen(format))
	{
		if (format[t.i] == '%')
		{
			init(&t);
			which_conv(format, t.i, &t);
			t.j += t.len_return;
			t.i += t.count + 1;
		}
		else
			printstr(format, &t);
	}
	va_end(t.arguments);
	return (t.j);
}

int		ft_printf(const char *format, ...)
{
	t_conv	t;

	t.fd = 1;
	init_start(&t);
	va_start(t.arguments, format);
	while (format[t.i] != '\0' && t.i <= (int)ft_strlen(format))
	{
		if (format[t.i] == '%')
		{
			init(&t);
			which_conv(format, t.i, &t);
			t.j += t.len_return;
			t.i += t.count + 1;
		}
		else
			printstr(format, &t);
	}
	va_end(t.arguments);
	return (t.j);
}
