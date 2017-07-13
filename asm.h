/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by aboudjem          #+#    #+#             */
/*   Updated: 2017/06/27 20:19:18 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "corewar.h"

# define CHECK_BIT(var, pos)	(var & pos)
# define NAME		1
# define COMM		2
# define SIZE		4
# define READ 		8
# define WRITE 		16
# define LABEL		32
# define REG 		1
# define DIR 		2
# define IND 		4

# define LIVE			"D"
# define LD				"DI,R"
# define ST				"R,IR"
# define ADD			"R,R,R"
# define SUB			"R,R,R"
# define AND			"RDI,RDI,R"
# define OR				"RDI,RDI,R"
# define XOR			"RDI,RDI,R"
# define ZJMP			"D"
# define LDI			"RDI,DR,R"
# define STI			"R,RDI,DR"
# define FORK			"D"
# define LLD			"DI,R"
# define LLDI			"RDI,DR,R"
# define LFORK			"D"
# define AFF			"R"

typedef struct			s_arg
{
	unsigned int		addr;
	char				pad[4];
	size_t				size;
	unsigned int		value;
	char				type;
	char				pad2[3];
	int					l;
	char				pad3[4];
	char				*name;
}						t_arg;

typedef struct			s_opc
{
	t_arg				*arg;
	struct s_opc		*next;
	struct s_opc		*back;
	char				*name;
	char				*opcode;
	int					label_size;
	int					need_ocp;
	unsigned int		addr;
	char				pad[4];
}						t_opc;

typedef struct			s_label
{
	t_opc				*opc;
	struct s_label		*next;
	struct s_label		*back;
	char				*name;
	unsigned int		addr;
	char				pad[4];
}						t_label;

typedef struct			s_check
{
	size_t				size;
	int					need_ocp;
	int					label_size;
	char				*mod;
	char				*name;
	char				*opcode;
	char				padding[8];
}						t_check;

typedef struct			s_asm
{
	t_label				*label;
	t_check				*check;
	t_header			header;
	int					opc_id;
	int					bit;
	unsigned int		size;
	char				pad2[4];
	char				*filename;
}						t_asm;

/*
** add_label.c
*/
t_label					*new_label(char *str);
void					add_label(t_label *label, char *str);

/*
** add_opc.c
*/
t_opc					*new_opc(t_opc opcode, t_arg *args);
void					add_opc(t_opc *opc, t_opc opcde, t_arg *args);

/*
** check_args.c
*/
void					check_arguments(t_asm *a, t_arg *args, char *line);

/*
** check_valid.c
*/
int						is_a_valid_label(char *label);
int						is_a_valid_register(char *str);
int						is_a_valid_direct(char *direct);
int						is_a_valid_indirect(char *indirect);
int						is_a_valid_opcode(t_asm *a, char *opcode);

/*
** create_file.c
*/
void					write_file(int fd, t_asm a);
void					write2_file(int fd, t_asm *a);
void					create_binary_file(char *name, t_asm *a);

/*
** define_addr.c
*/
void					define_addr(t_asm *a);

/*
** free_struct.c
*/
void					disp_opc(t_opc *opc);
void					free_tab(char **tab);
void					get_infos(char *line, t_header *header, t_asm *a);

/*
** get_instructs.c
*/
void					get_instructions(t_asm *a, char *line);

/*
** init.c
*/
t_check					*init_optab(void);
t_check					*init_optab2(t_check *tab);
void					init_asm_structure(t_asm *as);
void					init_check2(t_check *c, char *m, int ocp, int s);
void					init_check(t_check *c, char *n, char *opc, size_t s);

/*
** get_header.c
*/
void					get_name_and_comment(char *line, t_asm *a);

/*
** print_error.c
*/
void					debug_print_instructions(t_asm *a);
void					print_error(int id, char *m) __attribute__((noreturn));

/*
** stock_opc.c
*/
void					free_asm_structure(t_asm *a);
void					free_arg_structure(t_arg *arg);
void					free_opc_structure(t_opc *opc);
void					free_label_structure(t_label *label);

/*
** stock.c
*/
t_arg					*split_args(char *parameters);
int						stock_label(char *str, t_asm *a);
int						stock_opcode(char *name, t_asm *a, char *line);
t_arg					*stock_args(t_asm *a, char *instruction, char *line);
void					add_opc_to_label(t_label *l, t_opc opcode, t_arg *args);

/*
** tools.c
*/
int						get_nb(char *str);
char					*get_str(char *line);
void					remove_comment(char *line);
char					*get_first_word(char *line);
char					*remove_opcode(char *instruction);

/*
** tools2.c
*/
char					*clean_str(char *line);
int						empty_line(char *line);
char					*line_handler(char *line);
int						count_char(char *s, char c);
unsigned int			revert_hex(unsigned int x, size_t bytes);

/*
** tools3.c
*/
void					free_tab(char**tab);
char					*file_name(char *name);
size_t					count_args(t_arg *args);

#endif
