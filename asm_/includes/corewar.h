/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 03:43:57 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 03:43:58 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

# define BUFF_SIZE 	20
# define EOC      	"\033[0m"
# define BOLD       "\033[1m"
# define ITALIC     "\033[3m"
# define UNDERLINE  "\033[4m"
# define BLACK   	"\033[30m"
# define RED     	"\033[31m"
# define GREEN   	"\033[32m"
# define YELLOW  	"\033[33m"
# define BLUE   	"\033[34m"
# define MAGENTA 	"\033[35m"
# define CYAN    	"\033[36m"
# define WHITE   	"\033[37m"
# define COLOR		1

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	char						pad[3];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
	char						pad2[3];
}								t_header;

/*
** Struct GNL
*/

typedef struct					s_struct
{
	char						*s1;
	char						*s2;
	int							fd;
	int							pad;
	struct s_struct				*next;
	struct s_struct				*prev;
}								t_struct;

/*
** Struct FT_PRINTF
*/

typedef struct					s_type
{
	unsigned long long int		u;
	long long					d;
	unsigned int				c;
	int							count;
	int							len_return;
	int							i;
	int							j;
	int							fd;
	char						*print;
	char						*s;
	va_list						arguments;
	char						conv;
	char						pad[7];
}								t_conv;
/*
** Libft
*/

void							ft_putnbr(int n);
int								ft_isdigit(int c);
int								ft_isalpha(int c);
void							ft_putchar(char c);
int								ft_len_int(int nbr);
int								tab_len(char **tab);
void							ft_memdel(void **ap);
char							*ft_strtrim(char *s);
void							ft_free_tab(char **ptr);
char							*ft_strnew(size_t size);
int								ft_isdig_str(char *ptr);
int								ft_atoi(const char *str);
size_t							ft_strlen(const char *s);
void							ft_putstr(char const *s);
void							*ft_memalloc(size_t size);
char							*ft_strchr(char *s, int c);
char							*ft_strdup(const char *s1);
void							ft_bzero(void *s, size_t n);
void							ft_bzero(void *s, size_t n);
void							ft_putchar_fd(char c, int fd);
char							**ft_strsplit(char *s, char c);
int								ft_findchar(char *str, char c);
void							ft_putnbr_fd(long int n, int fd);
void							ft_putstr_fd(char const *s, int fd);
char							*ft_strstr(char *big, char *little);
char							*ft_strcat(char *s1, const char *s2);
char							*ft_strjoin(char *s1, char const *s2);
char							*ft_strcpy(char *dst, const char *src);
void							*ft_memset(void *b, int c, size_t len);
int								ft_strncmp(char *s1, char *s2, size_t n);
int								get_next_line(int const fd, char **line);
int								ft_strcmp(const char *s1, const char *s2);
void							ft_putlnbr_fd(unsigned long int n, int fd);
char							*ft_strncpy(char *d, const char *s, size_t l);
char							*ft_strsub(char const *s, size_t st, size_t l);

/*
** ft_printf.c
*/
void							init(t_conv *t);
void							conv_u(t_conv *t);
void							conv_s(t_conv *t);
void							conv_c(t_conv *t);
void							conv_d(t_conv *t);
void							init_start(t_conv *t);
void							len_return (t_conv *t);
char							next_conv(const char *s, int i);
void							get_conv(const char *s, t_conv *t);
void							printstr(const char *s, t_conv *t);
int								ft_printf(const char *format, ...);
int								ft_dprintf(int fd, const char *format, ...);
void							which_conv(const char *s, int i, t_conv *t);

#endif
