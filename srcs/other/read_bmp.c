/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 08:34:50 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/15 10:25:10 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

unsigned char	*read_bmp(char *filename, int *width, int *height)
{
	FILE			*file;
	int				offset;
	unsigned char	*str;
	int				size;

	file = fopen(filename, "rb");
	if (file == NULL)
		return (NULL);
	fseek(file, 10, SEEK_SET);
	fread(&offset, 4, 1, file);
	fseek(file, 18, SEEK_SET);
	fread(width, 4, 1, file);
	fread(height, 4, 1, file);
	fseek(file, offset, SEEK_END);
	size = ftell(file);
	fseek(file, offset, SEEK_SET);
	str = malloc(size + 1);
	fread(str, 1, size, file);
	fclose(file);
	str[size] = 0;
	return (str);
}
