/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 02:32:21 by aboudjem          #+#    #+#             */
/*   Updated: 2017/07/18 02:32:22 by aboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_newline(int fd, char *file)
{
	char buff[131072];

	ft_bzero(buff, 131072);
	while (read(fd, buff, 131072))
		;
	if (buff[ft_strlen(buff) - 1] != '\n')
		print_error(11, "");
	close(fd);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error(2, file);
}

static void	get_file_content(int fd, char *file, t_asm *a)
{
	char *line;

	check_newline(fd, file);
	while ((get_next_line(fd, &line)) > 0)
	{
		line = line_handler(line);
		if (!(CHECK_BIT(a->bit, SIZE)))
			get_name_and_comment(line, a);
		else if (CHECK_BIT(a->bit, SIZE) && !(empty_line(line)))
			get_instructions(a, line);
		free(line);
	}
	free(line);
	if (get_next_line(fd, &line) == 0 && CHECK_BIT(a->bit, READ))
		a->bit |= WRITE;
	free(line);
	close(fd);
}

static void	read_source_file(char *file, t_asm *a)
{
	int		fd;
	size_t	len;

	len = ft_strlen(file);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error(2, file);
	if (len < 3)
		print_error(3, file);
	if (file[len - 1] != 's' || file[len - 2] != '.')
		print_error(3, "");
	get_file_content(fd, file, a);
	if (!CHECK_BIT(a->bit, WRITE))
		print_error(10, "No instructions in file");
}

int			main(int argc, char **argv)
{
	t_asm		a;

	if (argc != 2)
		print_error(1, "");
	init_asm_structure(&a);
	read_source_file(argv[1], &a);
	create_binary_file(argv[1], &a);
	return (0);
}
